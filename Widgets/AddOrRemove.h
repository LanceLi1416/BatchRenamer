#ifndef BATCHRENAMER_ADDORREMOVE_H
#define BATCHRENAMER_ADDORREMOVE_H

#include <QPushButton>
#include <QWidget>

class AddOrRemove : public QWidget {
Q_OBJECT

public:
    AddOrRemove(const QString &addHint, const QString &remHint, QWidget *parent = nullptr);

    ~AddOrRemove() override = default;

    inline void setAddHint(const QString &toolTip) const;

    inline void setRemHint(const QString &toolTip) const;

public:
    QPushButton *btnAdd;
    QPushButton *btnRem;

};


#endif //BATCHRENAMER_ADDORREMOVE_H
