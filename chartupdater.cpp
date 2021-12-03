#include "chartupdater.h"
#include "abstractdirectorystrategy.h"

#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>
#include <QtCharts/QAbstractSeries>

#include "filestatmodel.h"

//#include <

ChartUpdater::ChartUpdater(const QSharedPointer<QtCharts::QChart> &chart
                           , CustomFileModel *model, QObject *parent)
    : QObject(parent)
    , m_chart(chart)
    , m_axisY(new QtCharts::QValueAxis)
    , m_sourceModel(model)
{
    m_chart->addAxis(m_axisY.data(), Qt::AlignLeft);
    connect(m_sourceModel, &CustomFileModel::layoutChanged, [this](){
        updateStatistics(m_sourceModel->getCachedStats());
    });
}

void ChartUpdater::setEnabled(bool enabled)
{
    m_enabled = enabled;
    if (enabled) {
        updateStatistics(m_sourceModel->getCachedStats());
    }
}

void ChartUpdater::updateStatistics(const QMap<QString, double> &cachedData)
{
    if (m_enabled) {
        m_chart->removeAllSeries(); // 1
        auto *series = createSeriesData(cachedData); // 2
        m_chart->addSeries(series); // 3
        afterUpdate(series); // 4
    }
}

QtCharts::QAbstractSeries* PieChartUpdater::createSeriesData(const QMap<QString, double> &cachedData)
{
    bool m_statIsGrouped = false;
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
    for (auto& name : cachedData.keys()) {
        series->append(!m_statIsGrouped ? QFileInfo(name).fileName() : name, cachedData[name]);
    }
    return series;
}

QtCharts::QAbstractSeries *BarChartUpdater::createSeriesData(const QMap<QString, double> &cachedData)
{
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();
    for (auto& name : cachedData.keys()) {
        QtCharts::QBarSet *set0 = new QtCharts::QBarSet(!m_statIsGrouped ? QFileInfo(name).fileName() : name);
        *set0<< cachedData[name];
        series->append(set0);
    }
    return series;
}

void BarChartUpdater::afterUpdate(QtCharts::QAbstractSeries *series)
{
    series->attachAxis(m_axisY.data());
}
