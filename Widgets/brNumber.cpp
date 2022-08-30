#include "brNumber.h"

#include <QCoreApplication>
#include <QGridLayout>
#include <QLabel>

#include "../Core.h"

brNumber::brNumber(QWidget *parent) : Pallet(parent) {
    static QString (*_translate)(const char *, const char *, const char *, int) = QCoreApplication::translate;

    this->cboMode = new QComboBox(this);
    this->cboMode->addItem(_translate("Number", "Find & Replace", nullptr, -1));
    this->cboMode->addItem(_translate("Number", "Number", nullptr, -1));
    this->cboMode->addItem(_translate("Number", "Set Extension", nullptr, -1));
    this->cboMode->addItem(_translate("Number", "Remove Text", nullptr, -1));
    this->cboMode->setCurrentIndex(1);

    auto *lblApplyTo = new QLabel(_translate("Number", "Apply To:", nullptr, -1), this);
    this->cboApplyTo = new QComboBox(this);
    this->cboApplyTo->addItem(_translate("Number", "Name Only", nullptr, -1));
    this->cboApplyTo->addItem(_translate("Number", "Extension Only", nullptr, -1));
    this->cboApplyTo->addItem(_translate("Number", "Name and Extension", nullptr, -1));

    auto *lblDigits = new QLabel(_translate("Number", "Digits:", nullptr, -1), this);
    this->spnDigits = new QSpinBox(this);
    this->spnDigits->setValue(4);

    auto *lblStart = new QLabel(_translate("Number", "Start value:", nullptr, -1), this);
    this->spnStart = new QSpinBox(this);
    this->spnStart->setValue(1);

    auto *lblStep = new QLabel(_translate("Number", "Step value:", nullptr, -1), this);
    this->spnStep = new QSpinBox(this);
    this->spnStep->setValue(1);

    auto *lblInsTxt = new QLabel(_translate("Number", "Insert text:", nullptr, -1), this);
    this->lneInsTxt = new QLineEdit(this);

    auto *lblFormat = new QLabel(_translate("Number", "Format:", nullptr, -1), this);
    this->cboFormat = new QComboBox(this);
    this->cboFormat->addItem(_translate("Number", "Original - text - number", nullptr, -1));
    this->cboFormat->addItem(_translate("Number", "Number - text - original", nullptr, -1));
    this->cboFormat->addItem(_translate("Number", "Text - number", nullptr, -1));
    this->cboFormat->addItem(_translate("Number", "Number - text", nullptr, -1));

    this->chkContinue = new QCheckBox(_translate("Number", "Continue Numbering", nullptr, -1), this);

    auto *grid = new QGridLayout(this);
    grid->addWidget(this->cboMode, 0, 0, 1, 2);
    grid->addWidget(lblApplyTo, 1, 0, 1, 1);
    grid->addWidget(this->cboApplyTo, 1, 1, 1, 1);
    grid->addWidget(lblDigits, 2, 0, 1, 1);
    grid->addWidget(this->spnDigits, 2, 1, 1, 1);
    grid->addWidget(lblStart, 3, 0, 1, 1);
    grid->addWidget(this->spnStart, 3, 1, 1, 1);
    grid->addWidget(lblStep, 4, 0, 1, 1);
    grid->addWidget(this->spnStep, 4, 1, 1, 1);
    grid->addWidget(lblInsTxt, 5, 0, 1, 1);
    grid->addWidget(this->lneInsTxt, 5, 1, 1, 1);
    grid->addWidget(lblFormat, 6, 0, 1, 1);
    grid->addWidget(this->cboFormat, 6, 1, 1, 1);
    grid->addWidget(this->chkContinue, 7, 1, 1, 1);
}

void brNumber::connectAll() {
    QObject::connect(this->cboMode, &QComboBox::currentIndexChanged, this, [this] { emit this->typeChanged(); });

    QObject::connect(this->cboApplyTo, &QComboBox::currentIndexChanged, this, [this] { emit this->valueChanged(); });
    QObject::connect(this->spnDigits, &QSpinBox::valueChanged, this, [this] { emit this->valueChanged(); });
    QObject::connect(this->spnStart, &QSpinBox::valueChanged, this, [this] { emit this->valueChanged(); });
    QObject::connect(this->spnStep, &QSpinBox::valueChanged, this, [this] { emit this->valueChanged(); });
    QObject::connect(this->lneInsTxt, &QLineEdit::textChanged, this, [this] { emit this->valueChanged(); });
    QObject::connect(this->cboFormat, &QComboBox::currentIndexChanged, this, [this] { emit this->valueChanged(); });
    QObject::connect(this->chkContinue, &QCheckBox::stateChanged, this, [this] { emit this->valueChanged(); });
}

QList<QFileInfo> &brNumber::applyChanges(const QList<QFileInfo> &files, QList<QFileInfo> &renamed) {
    return core::number(files,
                        renamed,
                        this->spnStart->value(),
                        this->spnStep->value(),
                        this->spnDigits->value(),
                        this->lneInsTxt->text(),
                        static_cast<core::MODE>(this->cboApplyTo->currentIndex()),
                        static_cast<core::FORMAT>(this->cboFormat->currentIndex()),
                        this->chkContinue->isChecked());
}
