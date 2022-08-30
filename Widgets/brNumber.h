#ifndef BATCHRENAMER_BRNUMBER_H
#define BATCHRENAMER_BRNUMBER_H

#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QWidget>

#include "Pallet.hpp"

class brNumber : public Pallet {
Q_OBJECT

public:
    explicit brNumber(QWidget *parent = nullptr);

    ~brNumber() override = default;

    void connectAll() override;

    QList<QFileInfo> &applyChanges(const QList<QFileInfo> &files, QList<QFileInfo> &renamed) override;

private:
    //QComboBox *cboMode;
    QComboBox *cboApplyTo;
    QSpinBox *spnDigits;
    QSpinBox *spnStart;
    QSpinBox *spnStep;
    QLineEdit *lneInsTxt;
    QComboBox *cboFormat;
    QCheckBox *chkContinue;
};


#endif //BATCHRENAMER_BRNUMBER_H
