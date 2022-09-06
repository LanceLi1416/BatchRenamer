#include "brNumber.h"

#include <QCoreApplication>
#include <QGridLayout>
#include <QLabel>

#include "../Core.h"

brNumber::brNumber(QWidget *parent) : Pallet(parent) {
    this->cboMode = new QComboBox(this);
    this->cboMode->addItem(tr("Find & Replace"));
    this->cboMode->addItem(tr("Number"));
    this->cboMode->addItem(tr("Set Extension"));
    this->cboMode->addItem(tr("Remove Text"));
    this->cboMode->setCurrentIndex(1);

    auto *lblApplyTo = new QLabel(tr("Apply To:"));
    this->cboApplyTo = new QComboBox(this);
    this->cboApplyTo->addItem(tr("Name Only"));
    this->cboApplyTo->addItem(tr("Extension Only"));
    this->cboApplyTo->addItem(tr("Name and Extension"));

    auto *lblDigits = new QLabel(tr("Digits:"));
    this->spnDigits = new QSpinBox(this);
    this->spnDigits->setValue(4);

    auto *lblStart = new QLabel(tr("Start value:"));
    this->spnStart = new QSpinBox(this);
    this->spnStart->setValue(1);

    auto *lblStep = new QLabel(tr("Step value:"));
    this->spnStep = new QSpinBox(this);
    this->spnStep->setValue(1);

    auto *lblInsTxt = new QLabel(tr("Insert text:"));
    this->lneInsTxt = new QLineEdit(this);

    auto *lblFormat = new QLabel(tr("Format:"));
    this->cboFormat = new QComboBox(this);
    this->cboFormat->addItem(tr("Original - text - number"));
    this->cboFormat->addItem(tr("Number - text - original"));
    this->cboFormat->addItem(tr("Text - number"));
    this->cboFormat->addItem(tr("Number - text"));

    this->chkContinue = new QCheckBox(tr("Continue Numbering"));

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
