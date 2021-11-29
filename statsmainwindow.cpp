#include "statsmainwindow.h"
#include "ui_statsmainwindow.h"

#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QFileSystemModel>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>

#include "filestatmodel.h"
#include "listfilestrategy.h"
#include "groupfilestrategy.h"
#include "chartupdater.h"
#include "abstractstatholder.h"

StatsMainWindow::StatsMainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StatsMainWindow)
    , m_treeModel(new QFileSystemModel(this))
    , m_tableModel(new CustomFileModel(this))
    , m_fileStatStrategy(QSharedPointer<ListFileStrategy>::create())
    , m_fileGroupStatStrategy(QSharedPointer<GroupFileStrategy>::create())
    , m_chart(new QtCharts::QChart)
    , m_chartView(new QtCharts::QChartView(m_chart.data(), this))
    , m_chartUpdater(new ChartUpdater(m_chart, this))
    , m_chartStatHolder(m_chartUpdater)
{
    ui->setupUi(this);

    connect(ui->choosePushButton, &QAbstractButton::clicked, this, &StatsMainWindow::onChooseButtonClicked);

    ui->listFilesRadioButton->setChecked(true);

    m_treeModel->setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
    ui->filesTreeView->setModel(m_treeModel);
    ui->filesTreeView->header()->setSectionResizeMode(QHeaderView::Stretch);

    ui->filesTableView->setModel(m_tableModel);
    ui->filesTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->filesTreeView->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &StatsMainWindow::onFilesTreeSelectionChanged);

    m_statHolders.push_back(m_tableModel);
    m_statHolders.push_back(m_chartStatHolder);

    connect(ui->listFilesRadioButton, &QRadioButton::toggled, this, &StatsMainWindow::updateStatsViews);
    connect(ui->groupFilesRadioButton, &QRadioButton::toggled, this, &StatsMainWindow::updateStatsViews);
    updateStatsViews();

    chooseTreeFolder(QDir::currentPath());
    ui->statsViewStackedWidget->setCurrentIndex(0); // table

    QVBoxLayout *layout = new QVBoxLayout(ui->chartPage);
    ui->chartPage->setLayout(layout);
    layout->setMargin(0);
    layout->addWidget(m_chartView);

    m_chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);

    connect(ui->statsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &StatsMainWindow::onStatsComboBoxIndexChanged);
}

StatsMainWindow::~StatsMainWindow()
{ }

void StatsMainWindow::chooseTreeFolder(const QString &path)
{
    ui->dirLineEdit->setText(path);
    ui->filesTreeView->setRootIndex(m_treeModel->setRootPath(path));

    if (!ui->filesTreeView->selectionModel()->selectedIndexes().isEmpty()) {
        handleTreeSelection(ui->filesTreeView->selectionModel()->selectedIndexes().first());
    }
}

void StatsMainWindow::handleTreeSelection(const QModelIndex &index)
{
    const QString currPath = m_treeModel->filePath(index);
    QFileInfo fileInfo = QFileInfo(currPath);
    m_currentStatRoot = fileInfo.isDir() ? currPath : fileInfo.absolutePath();
    updateStatsViews();
}

void StatsMainWindow::updateStatsViews()
{
    bool goodStats = ui->listFilesRadioButton->isChecked();

    for (AbstractStatHolder* statHolder : m_statHolders) {
        statHolder->setStatisticsStrategy(goodStats ? m_fileStatStrategy : m_fileGroupStatStrategy);
        statHolder->setStatsGrouped(!goodStats);
        statHolder->updateStatistics(m_currentStatRoot);
    }
}

void StatsMainWindow::onChooseButtonClicked()
{
    const QString path = QFileDialog::getExistingDirectory(this, "Выберите папку для статистики", QDir::currentPath());
    if (!path.isEmpty()) {
        chooseTreeFolder(path);
    }
}

void StatsMainWindow::onFilesTreeSelectionChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous)
    handleTreeSelection(current);
}

void StatsMainWindow::onStatsComboBoxIndexChanged(int index)
{
    ui->statsViewStackedWidget->setCurrentIndex(index > 0 ? 1 : 0);
    if (index == 1) {
        m_chartUpdater->setDisplayMode(ChartUpdater::PIE_MODE);
    }
    if (index == 2) {
        m_chartUpdater->setDisplayMode(ChartUpdater::BAR_MODE);
    }
}
