#include "filestatmodel.h"
#include "abstractdirectorystrategy.h"

#include <QFileInfo>

namespace  {
static constexpr double SIZE_PRESIZION = 0.0001;
}

CustomFileModel::CustomFileModel(QObject *parent)
    : QFileSystemModel(parent)
{
    connect(this, &QFileSystemModel::rootPathChanged, this, &CustomFileModel::onRootPathChanged);
}

int CustomFileModel::columnCount(const QModelIndex &parent) const
{
    int realColumnCount = QFileSystemModel::columnCount(parent);
    return realColumnCount + 1;
}

QVariant CustomFileModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && section == columnCount() - 1 && role == Qt::DisplayRole) {
        return QStringLiteral("Stats");
    }
    return QFileSystemModel::headerData(section, orientation, role);
}

QVariant CustomFileModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && index.column() == columnCount() - 1 && role == Qt::DisplayRole) {
        QString cacheKey;
        double statData;
        if (!m_statIsGrouped) {
            cacheKey = QFileInfo(filePath(index)).absoluteFilePath();
        } else {
            cacheKey = QFileInfo(filePath(index)).isDir()
                    ? "dir"
                    : QFileInfo(filePath(index)).suffix();
        }

        QString statDisplay;
        if (m_cachedStats.contains(cacheKey)) {
            statData = m_cachedStats[cacheKey];

            if (statData > SIZE_PRESIZION) {
                statDisplay = QString::number(statData * 100., 'f', 2) + "%";
            } else {
                statDisplay = "< 0.01%";
            }

            if (m_statIsGrouped) {
                statDisplay += QString(" (by type %1)").arg(cacheKey);
            }
        }
        return statDisplay;
    }

    return QFileSystemModel::data(index, role);
}

void CustomFileModel::updateStatisticsImpl(const QString &path)
{
    m_cachedStats = m_statStrategy->getDirectoryInfo(path);
    emit layoutChanged(); // force update view
}

void CustomFileModel::onRootPathChanged(const QString &newPath)
{
    updateStatistics(newPath);
}
