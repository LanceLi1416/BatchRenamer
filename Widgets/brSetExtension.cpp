#include "brSetExtension.h"

#include <QCoreApplication>
#include <QGridLayout>
#include <QLabel>

#include "../Core.h"

brSetExtension::brSetExtension(QWidget *parent) : Pallet(parent) {
    this->cboMode = new QComboBox(this);
    this->cboMode->addItem(tr("Find & Replace"));
    this->cboMode->addItem(tr("Number"));
    this->cboMode->addItem(tr("Set Extension"));
    this->cboMode->addItem(tr("Remove Text"));
    this->cboMode->setCurrentIndex(2);

    auto *lblExt = new QLabel(tr("Extension:"));
    this->lneExt = new QLineEdit(this);

    auto *grid = new QGridLayout(this);
    grid->addWidget(this->cboMode, 0, 0, 1, 2);
    grid->addWidget(lblExt, 1, 0, 1, 1);
    grid->addWidget(this->lneExt, 1, 1, 1, 1);
}

void brSetExtension::connectAll() {
    QObject::connect(this->cboMode, &QComboBox::currentIndexChanged, this, [this] { emit this->typeChanged(); });

    QObject::connect(this->lneExt, &QLineEdit::textChanged, this, [this] { emit this->valueChanged(); });
}

QList<QFileInfo> &brSetExtension::applyChanges(const QList<QFileInfo> &files, QList<QFileInfo> &renamed) {
    return core::set_extension(files, renamed, this->lneExt->text());
}
