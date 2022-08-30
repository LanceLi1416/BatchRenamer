#include "Spacer.h"

#include <QSizePolicy>

Spacer::Spacer(QWidget *parent) : QWidget(parent) {
    this->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
}
