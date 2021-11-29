#include "chartupdater.h"
#include "abstractdirectorystrategy.h"

#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>

ChartUpdater::ChartUpdater(const QSharedPointer<QtCharts::QChart> &chart, QObject *parent)
    : QObject(parent)
    , m_mode(PIE_MODE)
    , m_chart(chart)
    , m_axisY(new QtCharts::QValueAxis)
{
    m_chart->addAxis(m_axisY.data(), Qt::AlignLeft);
}

void ChartUpdater::setDisplayMode(ChartUpdater::DisplayMode mode)
{
    m_mode = mode;
    updateStatistics(m_path);
}

void ChartUpdater::updateStatisticsImpl(const QString& path)
{
    auto info = m_statStrategy->getDirectoryInfo(path);
    m_chart->removeAllSeries();

    if (m_mode == PIE_MODE)
    {
        QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
        for (auto& name : info.keys()) {
            series->append(!m_statIsGrouped ? QFileInfo(name).fileName() : name, info[name]);
        }
        m_chart->addSeries(series);
    }

    if (m_mode == BAR_MODE)
    {
        QtCharts::QBarSeries *series = new QtCharts::QBarSeries();
        for (auto& name : info.keys()) {
            QtCharts::QBarSet *set0 = new QtCharts::QBarSet(!m_statIsGrouped ? QFileInfo(name).fileName() : name);
            *set0<< info[name];
            series->append(set0);
        }
        m_chart->addSeries(series);
        series->attachAxis(m_axisY.data());
    }
}
