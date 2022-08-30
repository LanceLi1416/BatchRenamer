#include "brFindAndReplace.h"

#include "../Core.h"

#include <QCoreApplication>
#include <QGridLayout>
#include <QLabel>

brFindAndReplace::brFindAndReplace(QWidget *parent) : Pallet(parent) {
    auto *wgtMain = new QWidget();
    static QString (*_translate)(const char *, const char *, const char *, int) = QCoreApplication::translate;

    this->cboMode = new QComboBox(wgtMain);
    this->cboMode->addItem(_translate("FindAndReplace", "Find & Replace", nullptr, -1));
    this->cboMode->addItem(_translate("FindAndReplace", "Number", nullptr, -1));
    this->cboMode->addItem(_translate("FindAndReplace", "Set Extension", nullptr, -1));
    this->cboMode->addItem(_translate("FindAndReplace", "Remove Text", nullptr, -1));

    auto *lblApplyTo = new QLabel(_translate("FindAndReplace", "Apply To:", nullptr, -1), wgtMain);
    this->cboApplyTo = new QComboBox(wgtMain);
    this->cboApplyTo->addItem(_translate("FindAndReplace", "Name Only", nullptr, -1));
    this->cboApplyTo->addItem(_translate("FindAndReplace", "Extension Only", nullptr, -1));
    this->cboApplyTo->addItem(_translate("FindAndReplace", "Name and Extension", nullptr, -1));

    auto *lblFind = new QLabel(_translate("FindAndReplace", "Find:", nullptr, -1), wgtMain);
    this->lneFind = new QLineEdit(wgtMain);

    auto *lblRepl = new QLabel(_translate("FindAndReplace", "Replace:", nullptr, -1), wgtMain);
    this->lneRepl = new QLineEdit(wgtMain);

    this->chkCase = new QCheckBox(_translate("FindAndReplace", "Case Sensitive", nullptr, -1), wgtMain);
    this->chkFirst = new QCheckBox(_translate("FindAndReplace", "First Match Only", nullptr, -1), wgtMain);

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
