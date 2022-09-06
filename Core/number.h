#ifndef BR_CORE_NUMBER
#define BR_CORE_NUMBER

#include <QFileInfo>
#include <QString>

#include "../enums.h"

namespace core {
    QString number(const QString &name,
                   int num = 1,
                   int digits = 1,
                   const QString &insTxt = (QString &) "",
                   MODE mode = MODE::NAME,
                   FORMAT fmt = FORMAT::ORIG_TXT_NUM);

    QList<QFileInfo> &number(const QList<QFileInfo> &files,
                             QList<QFileInfo> &renamed,
                             int start = 1,
                             int step = 1,
                             int digits = 1,
                             const QString &insTxt = (QString &) "",
                             MODE mode = MODE::NAME,
                             FORMAT fmt = FORMAT::ORIG_TXT_NUM,
                             bool cont = false);
}


#endif //BR_CORE_NUMBER
