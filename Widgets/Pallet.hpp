#ifndef BATCHRENAMER_PALLET_HPP
#define BATCHRENAMER_PALLET_HPP

#include <QComboBox>
#include <QFileInfo>
#include <QWidget>

class Pallet : public QWidget {
Q_OBJECT

public:
    explicit Pallet(QWidget *parent = nullptr) : QWidget(parent) {}

    ~Pallet() override = default;

public:
    int getCurrentTypeIndex() { return this->cboMode->currentIndex(); }

    virtual void connectAll() {}

    virtual QList<QFileInfo> &applyChanges(const QList<QFileInfo> &files, QList<QFileInfo> &renamed) {
        return renamed;
    }

signals:

    void valueChanged();

    void typeChanged();

protected:
    QComboBox *cboMode;
};

#endif //BATCHRENAMER_PALLET_HPP
