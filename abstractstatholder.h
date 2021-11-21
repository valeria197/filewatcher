#pragma once

#include <QSharedPointer>
class AbstractDirectoryStrategy;

class AbstractStatHolder
{
public:
    virtual ~AbstractStatHolder() {}

    void setStatsGrouped(bool grouped);

    virtual void setStatisticsStrategy(const QSharedPointer<AbstractDirectoryStrategy> &strategy);

    void updateStatistics(const QString& path);

protected:
    virtual void updateStatisticsImpl(const QString& path) = 0;

protected:
    bool m_statIsGrouped = false;
    QSharedPointer<AbstractDirectoryStrategy> m_statStrategy = nullptr;
    QString m_path;
};
