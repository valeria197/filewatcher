#pragma once

#include <QFileInfo>
#include <QMap>

/*!
 * \brief The AbstractDirectoryStrategy будет использоваться в модельке, где папка существует.
 */
class AbstractDirectoryStrategy
{
public:
    virtual ~AbstractDirectoryStrategy() {}

    QMap<QString, double> getDirectoryInfo(const QString &path) const;

protected:
    virtual void traversePath(const QString &path, QHash<QString, qint64> &hash) const = 0;

private:
    QMap<QString, double> calculateStats(const QHash<QString, qint64> &sizes) const;
};
