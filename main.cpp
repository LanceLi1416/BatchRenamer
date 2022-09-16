#include <QApplication>
#include <QTranslator>

#include "Widgets/BatchRenamer.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Translation
    QTranslator translator;
    if (QLocale().language() != QLocale::English) {
        for (const QString &locale: QLocale::system().uiLanguages()) {
            if (translator.load(":/i18n/i18n/br_" + QLocale(locale).name())) {
                QApplication::installTranslator(&translator);
                break;
            }
        }
    }

    BatchRenamer w;
    w.show();
    return QApplication::exec();
}
