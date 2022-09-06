#include "set_extension.h"

#include <QDir>

QString core::set_extension(const QString &name,
                            const QString &ext) {
    qsizetype split = name.lastIndexOf('.');

    if (ext == "") // nothing to set
        return name.left(split);

    if (split == -1) // no extension
        return name + "." + ext;

    return name.left(split + 1).append(ext);
}

QList<QFileInfo> &core::set_extension(const QList<QFileInfo> &files,
                                      QList<QFileInfo> &renamed,
                                      const QString &ext) {
    if (files.size() != renamed.size())
        renamed.resize(files.size());

    for (qsizetype i = 0; i < files.length(); ++i)
        renamed[i] = QFileInfo(renamed[i].dir(),
                               set_extension(files[i].fileName(), ext));

    return renamed;
}
