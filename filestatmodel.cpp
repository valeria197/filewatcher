#include "filestatmodel.h"
#include "abstractdirectorystrategy.h"

#include <QFileInfo>

CustomFileModel::CustomFileModel(QObject *parent)
    : QAbstractTableModel(parent)
{ }

CustomFileModel::~CustomFileModel()
{ }

int CustomFileModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 2;
}

int CustomFileModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_cachedStats.count();
}

QVariant CustomFileModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal) {
        if (section == 0 && role == Qt::DisplayRole)
            return "Имя";

        if (section == 1 && role == Qt::DisplayRole)
            return "В процентах";
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

QVariant CustomFileModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && role == Qt::DisplayRole) {
        if (index.column() == 0) {
            return QFileInfo(m_cachedStats.keys()[index.row()]).fileName();
        }

        if (index.column() == 1) {
            double val = 100. * m_cachedStats.values()[index.row()];
            if (val < 0.01)
                return "< 0.01%";

            return QString::number(val, 'f', 2) + "%";
        }
    }

    return QVariant();
}

void CustomFileModel::setStatisticsStrategy(const QSharedPointer<AbstractDirectoryStrategy> &strategy)
{
    m_statStrategy = strategy;
}

void CustomFileModel::updateStatistics(const QString &path)
{
    if (m_statStrategy != nullptr) {
        m_cachedStats = m_statStrategy->getDirectoryInfo(path);
        emit layoutChanged();
    }
}

const QMap<QString, double> &CustomFileModel::getCachedStats() const
{
    return m_cachedStats;
}
