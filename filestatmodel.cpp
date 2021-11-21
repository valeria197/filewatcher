#include "filestatmodel.h"
#include "abstractdirectorystrategy.h"

#include <QFileInfo>

FileStatModel::FileStatModel(QObject *parent)
    : QFileSystemModel(parent)
{
    connect(this, &QFileSystemModel::rootPathChanged, [this](const QString& /*newPath*/) {
        if (m_statStrategy) {
            updateStatistics();
        }
    });
}

void FileStatModel::setStatisticsStrategy(const QSharedPointer<AbstractDirectoryStrategy> &strategy)
{
    m_statStrategy = strategy;
    updateStatistics();
}

void FileStatModel::updateStatistics()
{
    m_cachedStats = m_statStrategy->getDirectoryInfo(rootPath());
    emit layoutChanged(); // force update view
}

void FileStatModel::setStatsGrouped(bool grouped)
{
    m_statIsGrouped = grouped;
}

int FileStatModel::columnCount(const QModelIndex &parent) const
{
    int realColumnCount = QFileSystemModel::columnCount(parent);
    return realColumnCount + 1;
}

QVariant FileStatModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && section == columnCount() - 1 && role == Qt::DisplayRole) {
        return QStringLiteral("Stats");
    }
    return QFileSystemModel::headerData(section, orientation, role);
}

QVariant FileStatModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && index.column() == columnCount() - 1 && role == Qt::DisplayRole) {
        QString statData, cacheKey;
        if (!m_statIsGrouped) {
            cacheKey = QFileInfo(filePath(index)).absoluteFilePath();
        } else {
            cacheKey = QFileInfo(filePath(index)).isDir()
                    ? "dir"
                    : QFileInfo(filePath(index)).completeSuffix();
        }
        if (m_cachedStats.contains(cacheKey)) {
            statData = m_cachedStats[cacheKey];
            if (m_statIsGrouped) {
                statData += " (by type)";
            }
        }
        return statData;
    }

    return QFileSystemModel::data(index, role);
}
