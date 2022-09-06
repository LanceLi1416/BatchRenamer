#include "brToolBar.h"

#include <QCoreApplication>

#include "Spacer.h"

brToolBar::brToolBar(QWidget *parent) : QToolBar(parent) {
    this->btnRun = new QPushButton(tr("RUN"));

    this->addWidget(new Spacer());
    this->addWidget(this->btnRun);
    this->addWidget(new Spacer());
}