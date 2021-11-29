#include "abstractdirectorystrategy.h"

QMap<QString, double> AbstractDirectoryStrategy::getDirectoryInfo(const QString &path) const
{
    QHash<QString, qint64> sizes;
    traversePath(path, sizes);
    return calculateStats(sizes);
}

QMap<QString, double> AbstractDirectoryStrategy::calculateStats(const QHash<QString, qint64> &sizes) const
{
    auto vals = sizes.values();
    qint64 total = 0;
    for(const auto &val : vals) {
        total += val;
    }

    QMap<QString, double> result;
    for (const auto &name : sizes.keys()) {
        result[name] = 1. * sizes[name] / total;
    }
    return result;
}
