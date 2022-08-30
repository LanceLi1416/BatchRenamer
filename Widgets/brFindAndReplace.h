#ifndef BATCHRENAMER_BRFINDANDREPLACE_H
#define BATCHRENAMER_BRFINDANDREPLACE_H

#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QWidget>

#include "Pallet.hpp"

class brFindAndReplace : public Pallet {
Q_OBJECT

public:
    explicit brFindAndReplace(QWidget *parent = nullptr);

    ~brFindAndReplace() override = default;

    void connectAll() override;

    QList<QFileInfo> &applyChanges(const QList<QFileInfo> &files, QList<QFileInfo> &renamed) override;

private:
    //QComboBox *cboMode;
    QComboBox *cboApplyTo;
    QLineEdit *lneFind;
    QLineEdit *lneRepl;
    QCheckBox *chkCase;
    QCheckBox *chkFirst;
};


#endif //BATCHRENAMER_BRFINDANDREPLACE_H
