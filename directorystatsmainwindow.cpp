#include "directorystatsmainwindow.h"
#include "ui_directorystatsmainwindow.h"

#include <QDir>
#include <QFileDialog>
#include <QFileInfo>

#include "filestatmodel.h"
#include "listfilestrategy.h"
#include "groupfilestrategy.h"

#include <QDebug>

DirectoryStatsMainWindow::DirectoryStatsMainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DirectoryStatsMainWindow)
    , m_treeModel(new FileStatModel(this))
    , m_tableModel(new FileStatModel(this))
    , fileStatStrategy(QSharedPointer<ListFileStrategy>::create())
    , fileGroupStatStrategy(QSharedPointer<GroupFileStrategy>::create())
{
    ui->setupUi(this);

    // -------- config UI --------

    connect(ui->choosePushButton, &QAbstractButton::clicked, [this]{
        const QString path = QFileDialog::getExistingDirectory(this, "Выберите папку для статистики", QDir::currentPath());
        chooseTreeFolder(path);
    });
    ui->listFilesRadioButton->setChecked(true);

    m_treeModel->setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
    ui->filesTreeView->setModel(m_treeModel);
    ui->filesTreeView->header()->setSectionResizeMode(QHeaderView::Stretch);

    m_tableModel->setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
    ui->filesTableView->setModel(m_tableModel);
    ui->filesTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->filesTreeView->selectionModel(), &QItemSelectionModel::currentRowChanged
            , [this](const QModelIndex &current, const QModelIndex &/*previous*/) {
        handleTreeSelection(current);
    });

    // -------------
    auto strategyToggler =  [this]{
        bool goodStats = ui->listFilesRadioButton->isChecked();
        if (goodStats) {
            m_treeModel->setStatisticsStrategy(fileStatStrategy);
            m_tableModel->setStatisticsStrategy(fileStatStrategy);
        } else {
            m_treeModel->setStatisticsStrategy(fileGroupStatStrategy);
            m_tableModel->setStatisticsStrategy(fileGroupStatStrategy);
        }

        m_treeModel->updateStatistics();
        m_tableModel->updateStatistics();
        m_treeModel->setStatsGrouped(!goodStats);
        m_tableModel->setStatsGrouped(!goodStats);
    };

    connect(ui->listFilesRadioButton, &QRadioButton::toggled, this, strategyToggler);
    connect(ui->groupFilesRadioButton, &QRadioButton::toggled, this, strategyToggler);
    strategyToggler();

    // -------------
    chooseTreeFolder(QDir::currentPath());
}

DirectoryStatsMainWindow::~DirectoryStatsMainWindow()
{ }

void DirectoryStatsMainWindow::chooseTreeFolder(const QString &path)
{
    ui->dirLineEdit->setText(path);
    ui->filesTreeView->setRootIndex(m_treeModel->setRootPath(path));

    ui->filesTableView->setRootIndex(m_tableModel->setRootPath(""));

    if (!ui->filesTreeView->selectionModel()->selectedIndexes().isEmpty()) {
        handleTreeSelection(ui->filesTreeView->selectionModel()->selectedIndexes().first());
    } else {
        ui->filesTableView->hide();
    }
}

void DirectoryStatsMainWindow::handleTreeSelection(const QModelIndex &index)
{
    const QString currPath = m_treeModel->filePath(index);
    bool isDir = QFileInfo(currPath).isDir();
    ui->filesTableView->setVisible(isDir);
    if (isDir) {
        ui->filesTableView->setRootIndex(m_tableModel->setRootPath(currPath));
    }
}
