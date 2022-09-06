#include <QApplication>
#include <QTranslator>

#include "Widgets/BatchRenamer.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    qDebug() << QLocale();
    for (const QString &locale: uiLanguages) {
        const QString baseName = "br_" + QLocale(locale).name();
        qDebug() << baseName;
        if (translator.load(":/i18n/i18n/" + baseName)) {
            QApplication::installTranslator(&translator);
            break;
        }
    }

    BatchRenamer w;
    w.show();
    return QApplication::exec();
}
