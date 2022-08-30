#ifndef BATCHRENAMER_SPACER_H
#define BATCHRENAMER_SPACER_H

#include <QWidget>

class Spacer : public QWidget {
Q_OBJECT

public:
    explicit Spacer(QWidget *parent = nullptr);

    ~Spacer() override = default;
};


#endif //BATCHRENAMER_SPACER_H
