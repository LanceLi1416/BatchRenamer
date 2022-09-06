#include "find_and_replace.h"

#include <QDir>

QString core::find_and_replace(const QString &name,
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

QList<QFileInfo> &core::find_and_replace(const QList<QFileInfo> &files,
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

