#ifndef ABSTRACTDIRECTORYSTRATEGY_H
#define ABSTRACTDIRECTORYSTRATEGY_H

#include <QFileInfo>

/*!
 * \brief The AbstractDirectoryStrategy class -- пока не очень понятно задание, пусть будет stateless
 * Ничего не бросает, потому что будет использоваться в модельке, где папка существует.
 */
class AbstractDirectoryStrategy
{
public:
    using FileInfo = QPair<QString, QString>;

    virtual ~AbstractDirectoryStrategy() {}

    virtual QList<FileInfo> getDirectoryInfo(const QString &path) = 0;

protected:
    qint64 getTotalSize(const QString &path);

    static constexpr double SIZE_PRESIZION = 0.0001;

protected:
    QHash<QString, qint64> m_dirSizeCache; // optimization
};


#endif // ABSTRACTDIRECTORYSTRATEGY_H
