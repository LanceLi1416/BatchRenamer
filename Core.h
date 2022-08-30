#ifndef BATCHRENAMER_CORE_H
#define BATCHRENAMER_CORE_H

#include <QDir>
#include <QFileInfo>
#include <QString>

#include "enums.h"

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

    QString set_extension(const QString &name,
                          const QString &ext);

    QList<QFileInfo> &set_extension(const QList<QFileInfo> &files,
                                    QList<QFileInfo> &renamed,
                                    const QString &ext = (QString &) "");
}

#endif //BATCHRENAMER_CORE_H
