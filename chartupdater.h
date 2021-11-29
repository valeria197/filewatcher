#pragma once

#include "abstractstatholder.h"
#include <QObject>

namespace QtCharts {
    class QChart;
    class QValueAxis;
}

class ChartUpdater : public QObject, public AbstractStatHolder
{
    Q_OBJECT
public:
    enum DisplayMode {
        PIE_MODE,
        BAR_MODE
    };

    explicit ChartUpdater(const QSharedPointer<QtCharts::QChart> &chart, QObject *parent = nullptr);

    void setDisplayMode(DisplayMode mode);

protected:
    void updateStatisticsImpl(const QString& path) override;

private:
    DisplayMode m_mode;
    QSharedPointer<QtCharts::QChart> m_chart;
    QSharedPointer<QtCharts::QValueAxis> m_axisY;
};
