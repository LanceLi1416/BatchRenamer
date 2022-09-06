#include "BatchRenamer.h"

#include <QAction>
#include <QBoxLayout>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>

#include <algorithm>

#include "AddOrRemove.h"
#include "brFindAndReplace.h"
#include "brNumber.h"
#include "brRemoveText.h"
#include "brSetExtension.h"

BatchRenamer::BatchRenamer(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {
    this->setupUi();
    this->setupMenu();
    this->setupData();

    this->connectAll();
}

BatchRenamer::~BatchRenamer() {
    delete this->mapPallets;
    delete this->lstOrigNames;
    delete this->lstRenamed;
    delete this->openedFiles;
}

void BatchRenamer::setupUi() {
    this->setWindowTitle(tr("Batch Renamer"));
    this->resize(1280, 720);

    auto *wgtMain = new QWidget(this);

    this->toolbar = new brToolBar();
    this->addToolBar(this->toolbar);

    this->lstPallets = new QListWidget(wgtMain);
    this->aomPallets = new AddOrRemove(tr("Add a pallet"), tr("Remove selected pallet(s)"), this);
    this->aomFiles = new AddOrRemove(tr("Add files and folders"), tr("Remove selected files and folders"), this);
    this->tabFiles = new QTableWidget(0, 2, wgtMain);
    this->tabFiles->setHorizontalHeaderLabels({tr("Current Name"), tr("New Name")});

    this->lstPallets->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
    this->tabFiles->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
    // TODO: find a way to be able to select a specific text without editing, instead of the entire cell
    this->tabFiles->setEditTriggers(QAbstractItemView::NoEditTriggers);

    auto *vbxPallets = new QVBoxLayout();
    vbxPallets->addWidget(this->lstPallets);
    vbxPallets->addWidget(this->aomPallets);

    auto *grdFiles = new QGridLayout();
    grdFiles->addWidget(this->aomFiles, 0, 0, 1, 1);
    grdFiles->addWidget(this->tabFiles, 1, 0, 1, 1);

    auto *grid = new QGridLayout(wgtMain);
    grid->addLayout(vbxPallets, 0, 0, 1, 1);
    grid->addLayout(grdFiles, 0, 1, 1, 1);

    this->setCentralWidget(wgtMain);
    wgtMain->setLayout(grid);

    //auto *statusBar = new QStatusBar(this);
    //this->setStatusBar(statusBar);

    QMetaObject::connectSlotsByName(this);
}

void BatchRenamer::setupMenu() {
    auto *menuBar = new QMenuBar(this);

    // FILE ------------------------------------------------------------------------------------------------------------
    auto *mnuFile = new QMenu(tr("File"), this);

    auto *actApplyChanges = new QAction(tr("Apply Changes"), this);
    auto *actAddFiles = new QAction(tr("Add Files..."), this);
    auto *actRemSelected = new QAction(tr("Remove Selected Files"), this);
    auto *actRemAll = new QAction(tr("Remove All Files"), this);
    auto *actRemUnaffected = new QAction(tr("Remove Unaffected Files"), this);
    auto *actNewPallet = new QAction(tr("New Pallet"), this);
    auto *actRemSelectedPallets = new QAction(tr("Remove Selected Pallets"), this);
    auto *actRemAllPallets = new QAction(tr("Remove All Pallets"), this);
    auto *actCloseWindow = new QAction(tr("Close Window"), this);

    mnuFile->addAction(actApplyChanges);
    mnuFile->addAction(actAddFiles);
    mnuFile->addAction(actRemSelected);
    mnuFile->addAction(actRemAll);
    mnuFile->addAction(actRemUnaffected);
    mnuFile->addSeparator();
    mnuFile->addAction(actNewPallet);
    mnuFile->addAction(actRemSelectedPallets);
    mnuFile->addAction(actRemAllPallets);
    mnuFile->addSeparator();
    mnuFile->addAction(actCloseWindow);

    actApplyChanges->setShortcut(Qt::CTRL | Qt::Key_Return);
    actAddFiles->setShortcut(Qt::CTRL | Qt::Key_Equal);
    actRemSelected->setShortcut(Qt::CTRL | Qt::Key_Minus);
    actRemAll->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_Minus);
    //actRemUnaffected->setShortcut();
    actNewPallet->setShortcut(Qt::CTRL | Qt::Key_N);
    actRemSelectedPallets->setShortcut(Qt::Key_Backspace);
    //actRemAllPallets->setShortcut();
    actCloseWindow->setShortcut(Qt::CTRL | Qt::Key_W);

    QObject::connect(actApplyChanges, &QAction::triggered, this, &BatchRenamer::applyChanges);
    QObject::connect(actAddFiles, &QAction::triggered, this, &BatchRenamer::addFiles);
    QObject::connect(actRemSelected, &QAction::triggered, this, &BatchRenamer::removeSelectedFiles);
    QObject::connect(actRemAll, &QAction::triggered, this, &BatchRenamer::removeAllFiles);
    QObject::connect(actRemUnaffected, &QAction::triggered, this, &BatchRenamer::removeUnaffectedFiles);
    QObject::connect(actNewPallet, &QAction::triggered, this, &BatchRenamer::addPallet);
    QObject::connect(actRemSelectedPallets, &QAction::triggered, this, &BatchRenamer::remPallets);
    QObject::connect(actRemAllPallets, &QAction::triggered, this, &BatchRenamer::remAllPallets);
    QObject::connect(actCloseWindow, &QAction::triggered, this, &QMainWindow::close);

    // EDIT ------------------------------------------------------------------------------------------------------------
    auto *mnuEdit = new QMenu(tr("Edit"), this);

    // VIEW ------------------------------------------------------------------------------------------------------------
    auto *mnuView = new QMenu(tr("View"), this);

    // WINDOW ----------------------------------------------------------------------------------------------------------
    auto *mnuWind = new QMenu(tr("Window"), this);

    auto *actMinimize = new QAction(tr("Minimize"), this);
    auto *actZoom = new QAction(tr("Zoom"), this);

    mnuWind->addAction(actMinimize);
    mnuWind->addAction(actZoom);

    actMinimize->setShortcut(Qt::CTRL | Qt::Key_M);
    //actZoom->setShortcut();

    QObject::connect(actMinimize, &QAction::triggered, this, &QMainWindow::showMinimized);
    QObject::connect(actZoom, &QAction::triggered, this, [this] {
        this->isMaximized() ? this->showNormal() : this->showMaximized();
    });

    // HELP ------------------------------------------------------------------------------------------------------------
    auto *mnuHelp = new QMenu("Help", this);

    menuBar->addMenu(mnuFile);
    menuBar->addMenu(mnuEdit);
    menuBar->addMenu(mnuView);
    menuBar->addMenu(mnuWind);
    menuBar->addMenu(mnuHelp);

    this->setMenuBar(menuBar);
}

void BatchRenamer::setupData() {
    this->mapPallets = new QMap<QListWidgetItem *, Pallet *>();

    this->lstOrigNames = new QList<QFileInfo>();
    this->lstRenamed = new QList<QFileInfo>();
    this->openedFiles = new QStringList();

    this->dirLastOpened = new QDir(QDir::current());
}

void BatchRenamer::connectAll() {
    QObject::connect(this->aomPallets->btnAdd, &QPushButton::clicked, this, &BatchRenamer::addPallet);
    QObject::connect(this->aomPallets->btnRem, &QPushButton::clicked, this, &BatchRenamer::remPallets);

    QObject::connect(this->aomFiles->btnAdd, &QPushButton::clicked, this, &BatchRenamer::addFiles);
    QObject::connect(this->aomFiles->btnRem, &QPushButton::clicked, this, &BatchRenamer::removeSelectedFiles);

    QObject::connect(this->toolbar->btnRun, &QPushButton::clicked, this, &BatchRenamer::applyChanges);
}

void BatchRenamer::addPallet() {
    Pallet *pallet = new brFindAndReplace(this);
    auto *item = new QListWidgetItem();

    pallet->connectAll();
    QObject::connect(pallet, &Pallet::valueChanged, this, &BatchRenamer::updateFiles);
    QObject::connect(pallet, &Pallet::typeChanged, this,
                     [this, item, pallet] {
                         this->changePalletType(item,
                                                static_cast<gui::TYPE>(pallet->getCurrentTypeIndex()));
                     });

    this->lstPallets->insertItem(0, item);
    item->setSizeHint(pallet->sizeHint());
    this->lstPallets->setItemWidget(item, pallet);

    this->mapPallets->insert(item, pallet);

    this->updateFiles();
}

void BatchRenamer::changePalletType(QListWidgetItem *item, gui::TYPE type) {
    this->lstPallets->removeItemWidget(item);

    Pallet *newPallet;
    if (type == gui::TYPE::FIND_AND_REPL)
        newPallet = new brFindAndReplace(this);
    else if (type == gui::TYPE::NUM)
        newPallet = new brNumber(this);
    else if (type == gui::TYPE::SET_EXT)
        newPallet = new brSetExtension(this);
    else if (type == gui::TYPE::REM_TXT)
        newPallet = new brRemoveText(this);
    else
        throw std::exception();

    newPallet->connectAll();
    QObject::connect(newPallet, &Pallet::valueChanged, this, &BatchRenamer::updateFiles);
    QObject::connect(newPallet, &Pallet::typeChanged, this,
                     [this, item, newPallet] {
                         this->changePalletType(item,
                                                static_cast<gui::TYPE>(newPallet->getCurrentTypeIndex()));
                     });

    item->setSizeHint(newPallet->sizeHint());
    this->lstPallets->setItemWidget(item, newPallet);

    this->mapPallets->insert(item, newPallet);

    this->updateFiles();
}

void BatchRenamer::remPallets() {
    for (QListWidgetItem *item: this->lstPallets->selectedItems()) {
        this->mapPallets->remove(item);
        this->lstPallets->removeItemWidget(item);
        delete item;
    }

    this->updateFiles();
}

void BatchRenamer::remAllPallets() {
    this->mapPallets->clear();
    this->lstPallets->clear();

    this->updateFiles();
}

void BatchRenamer::addFiles() {
    qsizetype len = this->openedFiles->length();

    // TODO: also allow directories?
    this->openedFiles->append(QFileDialog::getOpenFileNames(this,
                                                            tr("Select Files to Rename"),
                                                            QDir::currentPath()));
    this->openedFiles->removeDuplicates();

    if (this->openedFiles->length() == len) return; // no new files

    //TODO: find a more efficient way
    this->removeAllFiles();
    for (qsizetype i = 0; i < this->openedFiles->length(); ++i) {
        auto file = QFileInfo((*this->openedFiles)[i]);
        this->lstOrigNames->append(file);
        this->lstRenamed->append(file);
        this->tabFiles->insertRow(i);

        this->tabFiles->setItem(i, 0, new QTableWidgetItem(file.fileName()));
    }
    this->updateFiles();
}

void BatchRenamer::removeSelectedFiles() {
    if (this->tabFiles->selectedItems().length() == 0) return; // nothing selected

    // TODO: find a more efficient way
    auto *rows = new QSet<int>();
    for (QTableWidgetItem *item: this->tabFiles->selectedItems())
        rows->insert(this->tabFiles->row(item));

    auto *lstRow = new QList<int>(rows->begin(), rows->end());
    std::sort(lstRow->begin(), lstRow->end());

    for (qsizetype i = lstRow->length() - 1; i > -1; --i) {
        this->tabFiles->removeRow((*lstRow)[i]);
        this->lstOrigNames->removeAt((*lstRow)[i]);
        this->lstRenamed->removeAt((*lstRow)[i]);
    }
}

void BatchRenamer::removeAllFiles() {
    this->lstOrigNames->clear();
    this->lstRenamed->clear();

    this->tabFiles->setRowCount(0);
}

void BatchRenamer::removeUnaffectedFiles() {
    auto *remove_indices = new QList<qsizetype>();

    for (qsizetype i = 0; i < this->lstOrigNames->length(); ++i)
        if ((*this->lstOrigNames)[i] == (*this->lstRenamed)[i])
            remove_indices->append(i);

    for (qsizetype i = remove_indices->length() - 1; i > -1; --i) {
        this->tabFiles->removeRow((*remove_indices)[i]);
        this->lstOrigNames->removeAt((*remove_indices)[i]);
        this->lstRenamed->removeAt((*remove_indices)[i]);
    }
}

void BatchRenamer::updateFiles() {
    *this->lstRenamed = *this->lstOrigNames; // reset renamed
    for (Pallet *pallet: *qAsConst(this->mapPallets))
        pallet->applyChanges(*this->lstRenamed, *this->lstRenamed);

    for (qsizetype i = 0; i < this->lstRenamed->length(); ++i)
        this->tabFiles->setItem(i, 1, new QTableWidgetItem((*this->lstRenamed)[i].fileName()));

    this->tabFiles->resizeColumnsToContents();
}

void BatchRenamer::applyChanges() {
    for (qsizetype i = 0; i < this->lstOrigNames->length(); ++i) {
        QFile::rename((*this->lstOrigNames)[i].absoluteFilePath(),
                      (*this->lstRenamed)[i].absoluteFilePath());

        (*this->lstOrigNames)[i] = QFileInfo((*this->lstRenamed)[i].dir(), (*this->lstRenamed)[i].fileName());
        this->tabFiles->setItem(i, 0, new QTableWidgetItem((*this->lstOrigNames)[i].fileName()));
    }
}