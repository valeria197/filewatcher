#include "groupfilestrategy.h"
#include <QDir>

namespace {
static const QString DIR_MIME = "dir";
}

QHash<QString, double> GroupFileStrategy::getDirectoryInfo(const QString &path)
{
    QHash<QString, double> result;

    if (!QFile::exists(path)) {
        return {};
    }

    const QFileInfo pathInfo(path);
    if (!pathInfo.isDir()) {
        result.insert(path, 1);
    }

    qint64 total = getTotalSize(pathInfo.absoluteFilePath()); // hope, caching works
    QHash<QString, qint64> typeSizes;

    QDir directory(path);
    for (const auto& it : directory.entryInfoList(QDir::Dirs | QDir::Files| QDir::NoDotAndDotDot
                                                  | QDir::Hidden | QDir::NoSymLinks, QDir::Name)) {
        qint64 current = getTotalSize(it.absoluteFilePath());
        QString typeName = it.isDir() ? DIR_MIME : it.suffix();
        typeSizes[typeName] += current;
    }

    for (const QString &typeName : typeSizes.keys()) {
        qint64 current = typeSizes[typeName];
        double percent = 1. * current / total;
        result.insert(typeName, percent);
    }

    return result;
}
