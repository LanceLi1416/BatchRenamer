#include "Core.h"

namespace core {
    QString find_and_replace(const QString &name,
                             const QString &find,
                             const QString &repl,
                             MODE mode,
                             bool cs,
                             bool first) {
        if (find == "") return name; // find nothing

        qsizetype split = name.lastIndexOf('.');

        if (split == -1 && mode == MODE::EXT)
            return name;

        if (first) {
            if (mode == MODE::NAME_AND_EXT)
                return name.left(-1).replace(
                        name.indexOf(find, 0, cs ? Qt::CaseSensitive : Qt::CaseInsensitive),
                        find.length(),
                        repl);
            else if (mode == MODE::NAME)
                return name.left(split).replace(
                        name.indexOf(find, 0, cs ? Qt::CaseSensitive : Qt::CaseInsensitive),
                        find.length(),
                        repl).append(name.mid(split));
            else if (mode == MODE::EXT)
                return name.left(-1).replace(
                        name.indexOf(find, split + 1, cs ? Qt::CaseSensitive : Qt::CaseInsensitive),
                        find.length(),
                        repl);
            else throw std::exception();
        } else {
            if (mode == MODE::NAME_AND_EXT)
                return name.left(-1).replace(
                        find,
                        repl,
                        cs ? Qt::CaseSensitive : Qt::CaseInsensitive);
            else if (mode == MODE::NAME)
                return name.left(split).replace(
                        find,
                        repl,
                        cs ? Qt::CaseSensitive : Qt::CaseInsensitive).append(name.mid(split));
            else if (mode == MODE::EXT)
                return name.left(split + 1).append(
                        name.mid(split + 1).replace(
                                find,
                                repl,
                                cs ? Qt::CaseSensitive : Qt::CaseInsensitive));
            else
                throw std::exception();
        }
    }

    QList<QFileInfo> &find_and_replace(const QList<QFileInfo> &files,
                                       QList<QFileInfo> &renamed,
                                       const QString &find,
                                       const QString &repl,
                                       const MODE &mode,
                                       const bool &cs,
                                       const bool &first) {
        if (files.size() != renamed.size())
            renamed.resize(files.size());

        for (qsizetype i = 0; i < files.length(); ++i)
            renamed[i] = QFileInfo(renamed[i].dir(),
                                   find_and_replace(files[i].fileName(),
                                                    find,
                                                    repl,
                                                    mode,
                                                    cs,
                                                    first));

        return renamed;
    }

    QString number(const QString &name,
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

    QList<QFileInfo> &number(const QList<QFileInfo> &files,
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

    QString set_extension(const QString &name,
                          const QString &ext) {
        qsizetype split = name.lastIndexOf('.');

        if (ext == "") // nothing to set
            return name.left(split);

        if (split == -1) // no extension
            return name + "." + ext;

        return name.left(split + 1).append(ext);
    }

    QList<QFileInfo> &set_extension(const QList<QFileInfo> &files,
                                    QList<QFileInfo> &renamed,
                                    const QString &ext) {
        if (files.size() != renamed.size())
            renamed.resize(files.size());

        for (qsizetype i = 0; i < files.length(); ++i)
            renamed[i] = QFileInfo(renamed[i].dir(),
                                   set_extension(files[i].fileName(),
                                                 ext));

        return renamed;
    }
}