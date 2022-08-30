#ifndef BATCHRENAMER_BRSETEXTENSION_H
#define BATCHRENAMER_BRSETEXTENSION_H

#include <QComboBox>
#include <QLineEdit>
#include <QWidget>

#include "Pallet.hpp"

class brSetExtension : public Pallet {
Q_OBJECT

public:
    explicit brSetExtension(QWidget *parent = nullptr);

    ~brSetExtension() override = default;

    void connectAll() override;

    QList<QFileInfo> &applyChanges(const QList<QFileInfo> &files, QList<QFileInfo> &renamed) override;

private:
    //QComboBox *cboMode;
    QLineEdit *lneExt;
};


#endif //BATCHRENAMER_BRSETEXTENSION_H
