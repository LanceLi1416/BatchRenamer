#ifndef BATCHRENAMER_BATCHRENAMER_H
#define BATCHRENAMER_BATCHRENAMER_H

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>

#include "Pallet.hpp"

#include "../enums.h"

class BatchRenamer : public QMainWindow {
Q_OBJECT
public:
    explicit BatchRenamer(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

    ~BatchRenamer() override;

public slots:

    void addPallet();

    void remPallets();

    void remAllPallets();

    void addFiles();

    void removeSelectedFiles();

    void removeAllFiles();

    void removeUnaffectedFiles();

    void updateFiles();

    void applyChanges();

private:
    void setupUi();

    void setupMenu();

    void setupData();

    void connectAll();

    void changePalletType(QListWidgetItem *item, gui::TYPE type = gui::TYPE::FIND_AND_REPL);

private:
    QListWidget *lstPallets{};
    QTableWidget *tabFiles{};
    QPushButton *btnRun{};
    QPushButton *btnAddPallets{};
    QPushButton *btnRemPallets{};
    QPushButton *btnAddFiles{};
    QPushButton *btnRemFiles{};

    QMap<QListWidgetItem *, Pallet *> *mapPallets{};
    QList<QFileInfo> *lstOrigNames{};
    QList<QFileInfo> *lstRenamed{};
    QStringList *openedFiles{};

    QDir *dirLastOpened{};
};


#endif //BATCHRENAMER_BATCHRENAMER_H
