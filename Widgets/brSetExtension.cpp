#include "brSetExtension.h"

#include <QCoreApplication>
#include <QGridLayout>
#include <QLabel>

#include "../Core.h"

brSetExtension::brSetExtension(QWidget *parent) : Pallet(parent) {
    static QString (*_translate)(const char *, const char *, const char *, int) = QCoreApplication::translate;

    this->cboMode = new QComboBox(this);
    this->cboMode->addItem(_translate("SetExtension", "Find & Replace", nullptr, -1));
    this->cboMode->addItem(_translate("SetExtension", "Number", nullptr, -1));
    this->cboMode->addItem(_translate("SetExtension", "Set Extension", nullptr, -1));
    this->cboMode->addItem(_translate("SetExtension", "Remove Text", nullptr, -1));
    this->cboMode->setCurrentIndex(2);

    auto *lblExt = new QLabel(_translate("SetExtension", "Extension:", nullptr, -1), this);
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
