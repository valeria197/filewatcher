#include "listfilestrategy.h"
#include <QDir>

QHash<QString, double> ListFileStrategy::getDirectoryInfo(const QString &path)
{
    QHash<QString, double> result;

    if (!QFile::exists(path)) {
        return {};
    }

    const QFileInfo pathInfo(path);
    if (!pathInfo.isDir()) {
        result.insert(path, 1);
    }

    qint64 total = getTotalSize(pathInfo.absoluteFilePath());

    QDir directory(path);
    for (const auto& it : directory.entryInfoList(QDir::Dirs | QDir::Files| QDir::NoDotAndDotDot
                                                  | QDir::Hidden | QDir::NoSymLinks, QDir::Name)) {
        qint64 current = getTotalSize(it.absoluteFilePath());
        double percent = 1. * current / total;
        result.insert(it.absoluteFilePath(), percent);
    }

    return result;
}
