#include "listfilestrategy.h"
#include <QDir>

QHash<QString, QString> ListFileStrategy::getDirectoryInfo(const QString &path)
{
    QHash<QString, QString> result;

    if (!QFile::exists(path)) {
        return {};
    }

    const QFileInfo pathInfo(path);
    if (!pathInfo.isDir()) {
        result.insert(path, QStringLiteral("100%"));
    }

    qint64 total = getTotalSize(pathInfo.absoluteFilePath()); // hope, caching works

    QDir directory(path);
    for (const auto& it : directory.entryInfoList(QDir::Dirs | QDir::Files| QDir::NoDotAndDotDot
                                                  | QDir::Hidden | QDir::NoSymLinks, QDir::Name)) {
        qint64 current = getTotalSize(it.absoluteFilePath());
        double percent = 1. * current / total;
        if (percent > SIZE_PRESIZION) {
            result.insert(it.absoluteFilePath(), QString::number(percent * 100, 'f', 2) + "%");
        } else {
            result.insert(it.absoluteFilePath(), QString("< 0.01%"));
        }
    }

    return result;
}
