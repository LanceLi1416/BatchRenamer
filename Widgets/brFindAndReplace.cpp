#include "brFindAndReplace.h"

#include "../Core.h"

#include <QCoreApplication>
#include <QGridLayout>
#include <QLabel>

brFindAndReplace::brFindAndReplace(QWidget *parent) : Pallet(parent) {
    this->cboMode = new QComboBox(this);
    this->cboMode->addItem(tr("Find & Replace"));
    this->cboMode->addItem(tr("Number"));
    this->cboMode->addItem(tr("Set Extension"));
    this->cboMode->addItem(tr("Remove Text"));

    auto *lblApplyTo = new QLabel(tr("Apply To:"));
    this->cboApplyTo = new QComboBox(this);
    this->cboApplyTo->addItem(tr("Name Only"));
    this->cboApplyTo->addItem(tr("Extension Only"));
    this->cboApplyTo->addItem(tr("Name and Extension"));

    auto *lblFind = new QLabel(tr("Find:"));
    this->lneFind = new QLineEdit(this);

    auto *lblRepl = new QLabel(tr("Replace:"));
    this->lneRepl = new QLineEdit(this);

    this->chkCase = new QCheckBox(tr("Case Sensitive"));
    this->chkFirst = new QCheckBox(tr("First Match Only"));

    auto *grid = new QGridLayout(this);
    grid->addWidget(this->cboMode, 0, 0, 1, 2);
    grid->addWidget(lblApplyTo, 1, 0, 1, 1);
    grid->addWidget(this->cboApplyTo, 1, 1, 1, 1);
    grid->addWidget(lblFind, 2, 0, 1, 1);
    grid->addWidget(this->lneFind, 2, 1, 1, 1);
    grid->addWidget(lblRepl, 3, 0, 1, 1);
    grid->addWidget(this->lneRepl, 3, 1, 1, 1);
    grid->addWidget(this->chkCase, 4, 1, 1, 1);
    grid->addWidget(this->chkFirst, 5, 1, 1, 1);
}

void brFindAndReplace::connectAll() {
    QObject::connect(this->cboMode, &QComboBox::currentIndexChanged, this, [this] { emit this->typeChanged(); });

    QObject::connect(this->cboApplyTo, &QComboBox::currentIndexChanged, this, [this] { emit this->valueChanged(); });
    QObject::connect(this->lneFind, &QLineEdit::textChanged, this, [this] { emit this->valueChanged(); });
    QObject::connect(this->lneRepl, &QLineEdit::textChanged, this, [this] { emit this->valueChanged(); });
    QObject::connect(this->chkCase, &QCheckBox::stateChanged, this, [this] { emit this->valueChanged(); });
    QObject::connect(this->chkFirst, &QCheckBox::stateChanged, this, [this] { emit this->valueChanged(); });
}

QList<QFileInfo> &brFindAndReplace::applyChanges(const QList<QFileInfo> &files, QList<QFileInfo> &renamed) {
    return core::find_and_replace(files,
                                  renamed,
                                  this->lneFind->text(),
                                  this->lneRepl->text(),
                                  static_cast<core::MODE>(this->cboApplyTo->currentIndex()),
                                  this->chkCase->isChecked(),
                                  this->chkFirst->isChecked());
}
