#include "brRemoveText.h"

#include <QCoreApplication>
#include <QLabel>
#include <QGridLayout>

#include "../Core.h"

brRemoveText::brRemoveText(QWidget *parent) : Pallet(parent) {
    static QString (*_translate)(const char *, const char *, const char *, int) = QCoreApplication::translate;

    this->cboMode = new QComboBox(this);
    this->cboMode->addItem(_translate("RemoveText", "Find & Replace", nullptr, -1));
    this->cboMode->addItem(_translate("RemoveText", "Number", nullptr, -1));
    this->cboMode->addItem(_translate("RemoveText", "Set Extension", nullptr, -1));
    this->cboMode->addItem(_translate("RemoveText", "Remove Text", nullptr, -1));
    this->cboMode->setCurrentIndex(3);

    auto *lblRem = new QLabel(_translate("RemoveText", "Remove:", nullptr, -1), this);
    this->lneRem = new QLineEdit(this);

    this->chkFirst = new QCheckBox(_translate("RemoveText", "First Match Only", nullptr, -1), this);

    auto *grid = new QGridLayout(this);
    grid->addWidget(this->cboMode, 0, 0, 1, 2);
    grid->addWidget(lblRem, 1, 0, 1, 1);
    grid->addWidget(this->lneRem, 1, 1, 1, 1);
    grid->addWidget(this->chkFirst, 2, 1, 1, 1);
}

void brRemoveText::connectAll() {
    QObject::connect(this->cboMode, &QComboBox::currentIndexChanged, this, [this] { emit this->typeChanged(); });

    QObject::connect(this->lneRem, &QLineEdit::textChanged, this, [this] { emit this->valueChanged(); });
    QObject::connect(this->chkFirst, &QCheckBox::stateChanged, this, [this] { emit this->valueChanged(); });
}

QList<QFileInfo> &brRemoveText::applyChanges(const QList<QFileInfo> &files, QList<QFileInfo> &renamed) {
    return core::find_and_replace(files,
                                  renamed,
                                  this->lneRem->text(),
                                  (QString &) "",
                                  core::MODE::NAME_AND_EXT,
                                  chkFirst->isChecked());
}
