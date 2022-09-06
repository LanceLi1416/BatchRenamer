#ifndef BR_CORE_FIND_AND_REPLACE
#define BR_CORE_FIND_AND_REPLACE

#include <QFileInfo>
#include <QString>

#include "../enums.h"

namespace core {
    QString find_and_replace(const QString &name,
                             const QString &find,
                             const QString &repl,
                             MODE mode = MODE::NAME,
                             bool cs = false,
                             bool first = false);

    QList<QFileInfo> &find_and_replace(const QList<QFileInfo> &files,
                                       QList<QFileInfo> &renamed,
                                       const QString &find,
                                       const QString &repl,
                                       const MODE &mode = MODE::NAME,
                                       const bool &cs = false,
                                       const bool &first = false);
}

#endif //BR_CORE_FIND_AND_REPLACE