#include "number.h"

#include <QDir>

QString core::number(const QString &name,
                     const int num,
                     const int digits,
                     const QString &insTxt,
                     const MODE mode,
                     const FORMAT fmt) {
    QString numStr = QString::number(num);
    numStr.insert(0, QString(digits - numStr.length(), '0'));

    qsizetype split = name.lastIndexOf('.');

    if (split == -1 && mode == MODE::EXT)
        return name;

    if (mode == MODE::NAME_AND_EXT) {
        if (fmt == FORMAT::ORIG_TXT_NUM)
            return name + insTxt + numStr;
        else if (fmt == FORMAT::NUM_TXT_ORIG)
            return numStr + insTxt + name;
        else if (fmt == FORMAT::TXT_NUM)
            return insTxt + numStr;
        else if (fmt == FORMAT::NUM_TXT)
            return numStr + insTxt;
        else
            throw std::exception();
    } else if (mode == MODE::NAME) {
        if (fmt == FORMAT::ORIG_TXT_NUM)
            return name.left(split) + insTxt + numStr + name.mid(split);
        else if (fmt == FORMAT::NUM_TXT_ORIG)
            return numStr + insTxt + name;
        else if (fmt == FORMAT::TXT_NUM)
            return insTxt + numStr + name.mid(split);
        else if (fmt == FORMAT::NUM_TXT)
            return numStr + insTxt + name.mid(split);
        else
            throw std::exception();
    } else if (mode == MODE::EXT) {
        if (fmt == FORMAT::ORIG_TXT_NUM)
            return name + insTxt + numStr;
        else if (fmt == FORMAT::NUM_TXT_ORIG)
            return name.left(split + 1) + numStr + insTxt + name.mid(split + 1);
        else if (fmt == FORMAT::TXT_NUM)
            return name.left(split + 1) + insTxt + numStr;
        else if (fmt == FORMAT::NUM_TXT)
            return name.left(split + 1) + numStr + insTxt;
        else
            throw std::exception();
    } else
        throw std::exception();
}

QList<QFileInfo> &core::number(const QList<QFileInfo> &files,
                               QList<QFileInfo> &renamed,
                               const int start,
                               const int step,
                               const int digits,
                               const QString &insTxt,
                               const MODE mode,
                               const FORMAT fmt,
                               const bool cont) {
    if (files.size() != renamed.size())
        renamed.resize(files.size());

    if (cont) {
        for (qsizetype i = 0; i < files.length(); ++i)
            renamed[i] = QFileInfo(renamed[i].dir(),
                                   number(files[i].fileName(),
                                          start + i * step,
                                          digits,
                                          insTxt,
                                          mode,
                                          fmt));
    } else {
        auto *dirs = new QMap<QString, quint16>();

        for (qsizetype i = 0; i < files.length(); ++i) {
            if (!dirs->contains(files[i].dir().absolutePath()))
                dirs->insert(files[i].dir().absolutePath(), -1);

            (*dirs)[files[i].dir().absolutePath()] += 1;

            renamed[i] = QFileInfo(renamed[i].dir(),
                                   number(files[i].fileName(),
                                          start + dirs->value(files[i].dir().absolutePath()) * step,
                                          digits,
                                          insTxt,
                                          mode,
                                          fmt));
        }

        delete dirs;
    }


    return renamed;
}
