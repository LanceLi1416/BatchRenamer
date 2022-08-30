#ifndef BATCHRENAMER_BRTOOLBAR_H
#define BATCHRENAMER_BRTOOLBAR_H

#include <QPushButton>
#include <QToolBar>

class brToolBar : public QToolBar {
Q_OBJECT

public:
    explicit brToolBar(QWidget *parent = nullptr);

    ~brToolBar() override = default;

public:
    QPushButton *btnRun;
};


#endif //BATCHRENAMER_BRTOOLBAR_H
