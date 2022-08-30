#ifndef BATCHRENAMER_BRREMOVETEXT_H
#define BATCHRENAMER_BRREMOVETEXT_H

#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QWidget>

#include "Pallet.hpp"

class brRemoveText : public Pallet {
Q_OBJECT

public:
    explicit brRemoveText(QWidget *parent = nullptr);

    ~brRemoveText() override = default;

    void connectAll() override;

    QList<QFileInfo> &applyChanges(const QList<QFileInfo> &files, QList<QFileInfo> &renamed) override;

private:
    //QComboBox *cboMode;
    QLineEdit *lneRem;
    QCheckBox *chkFirst;
};


#endif //BATCHRENAMER_BRREMOVETEXT_H
