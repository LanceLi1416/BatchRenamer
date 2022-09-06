#ifndef BR_CORE_SET_EXTENSION
#define BR_CORE_SET_EXTENSION

#include <QFileInfo>
#include <QString>

namespace core {
    QString set_extension(const QString &name,
                          const QString &ext);

    QList<QFileInfo> &set_extension(const QList<QFileInfo> &files,
                                    QList<QFileInfo> &renamed,
                                    const QString &ext = (QString &) "");
}


#endif //BR_CORE_SET_EXTENSION
