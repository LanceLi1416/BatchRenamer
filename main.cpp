#include <QApplication>

#include "Widgets/BatchRenamer.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    BatchRenamer w;
    w.show();
    return QApplication::exec();
}
