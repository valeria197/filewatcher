#pragma once

#include <QObject>
#include <QSharedPointer>

namespace QtCharts {
    class QChart;
    class QValueAxis;
    class QAbstractSeries;
}

class AbstractDirectoryStrategy;
class CustomFileModel;

class ChartUpdater : public QObject
{
    Q_OBJECT
public:
    explicit ChartUpdater(const QSharedPointer<QtCharts::QChart> &chart,
                          CustomFileModel* model,
                          QObject *parent = nullptr);

    void setEnabled(bool enabled);

public slots:
    void updateStatistics(const QMap<QString, double>&  cachedData);

protected:
    virtual QtCharts::QAbstractSeries* createSeriesData(const QMap<QString, double>&  cachedData) = 0;
    virtual void afterUpdate(QtCharts::QAbstractSeries *series) {}

protected:
    QSharedPointer<QtCharts::QChart> m_chart;
    QSharedPointer<QtCharts::QValueAxis> m_axisY;
    CustomFileModel *m_sourceModel = nullptr;

    bool m_statIsGrouped = false;
    bool m_enabled = false;
};

class PieChartUpdater: public ChartUpdater
{
public:
    using ChartUpdater::ChartUpdater;

protected:
    QtCharts::QAbstractSeries*  createSeriesData(const QMap<QString, double>&  cachedData) override;
};

class BarChartUpdater: public ChartUpdater
{
public:
    using ChartUpdater::ChartUpdater;

protected:
    QtCharts::QAbstractSeries*  createSeriesData(const QMap<QString, double>&  cachedData) override;
    void afterUpdate(QtCharts::QAbstractSeries *series) override;
};
