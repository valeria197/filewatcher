#pragma once

#include <QWidget>

namespace Ui {
class StatsMainWindow;
}

namespace QtCharts {
    class QChartView;
    class QChart;
}

class QModelIndex;
class QFileSystemModel;
class AbstractDirectoryStrategy;
class AbstractStatHolder;
class CustomFileModel;
class ChartUpdater;

class StatsMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StatsMainWindow(QWidget *parent = nullptr);
    ~StatsMainWindow();

private:
    void chooseTreeFolder(const QString &path);
    void handleTreeSelection(const QModelIndex &index);

private slots:
    void updateStatsViews();
    void onChooseButtonClicked();
    void onFilesTreeSelectionChanged(const QModelIndex &current, const QModelIndex &previous);
    void onStatsComboBoxIndexChanged(int index);

private:
    const QSharedPointer<Ui::StatsMainWindow> ui;
    QFileSystemModel *m_treeModel;
    CustomFileModel *m_tableModel;

    QSharedPointer<AbstractDirectoryStrategy> m_fileStatStrategy;
    QSharedPointer<AbstractDirectoryStrategy> m_fileGroupStatStrategy;

    QSharedPointer<QtCharts::QChart> m_chart;
    QtCharts::QChartView *m_chartView;
    ChartUpdater    *m_chartUpdater;

    AbstractStatHolder* m_chartStatHolder;
    QList<AbstractStatHolder*> m_statHolders;

    QString m_currentStatRoot;
};
