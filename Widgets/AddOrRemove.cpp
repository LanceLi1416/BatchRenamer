#include "AddOrRemove.h"

#include <QCoreApplication>
#include <QGridLayout>
#include <QLabel>

AddOrRemove::AddOrRemove(const QString &addHint, const QString &remHint, QWidget *parent) : QWidget(parent) {
    this->btnAdd = new QPushButton("+", this);
    auto *wgtHLine = new QLabel("|", this);
    this->btnRem = new QPushButton("-", this);

    wgtHLine->setFixedWidth(2);
    wgtHLine->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    this->setAddHint(addHint);
    this->setRemHint(remHint);

    auto *grid = new QGridLayout(this);
    grid->addWidget(this->btnAdd, 0, 0, 1, 1);
    grid->addWidget(wgtHLine, 0, 1, 1, 1);
    grid->addWidget(this->btnRem, 0, 2, 1, 1);
}

inline void AddOrRemove::setAddHint(const QString &toolTip) const {
    this->btnAdd->setToolTip(toolTip);
}

inline void AddOrRemove::setRemHint(const QString &toolTip) const {
    this->btnRem->setToolTip(toolTip);
}

