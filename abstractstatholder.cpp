#include "abstractstatholder.h"

void AbstractStatHolder::setStatsGrouped(bool grouped)
{
    m_statIsGrouped = grouped;
}

void AbstractStatHolder::setStatisticsStrategy(const QSharedPointer<AbstractDirectoryStrategy> &strategy)
{
    m_statStrategy = strategy;
//    updateStatistics(m_path);
}

void AbstractStatHolder::updateStatistics(const QString &path)
{
    m_path = path;
    if (!m_statStrategy || path.isEmpty()) {
        return;
    }
    updateStatisticsImpl(path);
}
