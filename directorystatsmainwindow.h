#pragma once

#include <QWidget>

namespace Ui {
class DirectoryStatsMainWindow;
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

class DirectoryStatsMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DirectoryStatsMainWindow(QWidget *parent = nullptr);
    ~DirectoryStatsMainWindow();

private:
    void chooseTreeFolder(const QString &path);
    void handleTreeSelection(const QModelIndex &index);

private slots:
    void updateStatsViews();
    void onChooseButtonClicked();
    void onFilesTreeSelectionChanged(const QModelIndex &current, const QModelIndex &previous);
    void onStatsComboBoxIndexChanged(int index);

private:
    const QSharedPointer<Ui::DirectoryStatsMainWindow> ui;
    QFileSystemModel *m_treeModel;
    CustomFileModel *m_tableModel;

    QSharedPointer<AbstractDirectoryStrategy> m_fileStatStrategy;
    QSharedPointer<AbstractDirectoryStrategy> m_fileGroupStatStrategy;

    QSharedPointer<QtCharts::QChart> m_chart;
    QtCharts::QChartView *m_chartView;
    ChartUpdater    *m_chartUpdater;

    AbstractStatHolder* m_chartStatHolder;
    QList<AbstractStatHolder*> m_statHolders;
};
