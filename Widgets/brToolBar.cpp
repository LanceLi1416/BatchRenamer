#include "brToolBar.h"

#include <QCoreApplication>

#include "Spacer.h"

brToolBar::brToolBar(QWidget *parent) : QToolBar(parent) {
    static QString (*_translate)(const char *, const char *, const char *, int) = QCoreApplication::translate;

    this->btnRun = new QPushButton(_translate("Toolbar", "RUN", nullptr, -1));

    this->addWidget(new Spacer());
    this->addWidget(this->btnRun);
    this->addWidget(new Spacer());
}