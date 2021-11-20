#include "directorystatsmainwindow.h"
#include "ui_directorystatsmainwindow.h"

#include <QDir>
#include <QFileDialog>
#include <QFileInfo>

#include "filestatmodel.h"

#include <QDebug>

DirectoryStatsMainWindow::DirectoryStatsMainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DirectoryStatsMainWindow)
{
    ui->setupUi(this);

    // -------- config UI --------

    connect(ui->choosePushButton, &QAbstractButton::clicked, [this]{
        const QString path = QFileDialog::getExistingDirectory(this, "Выберите папку для статистики", QDir::currentPath());
        chooseTreeFolder(path);
    });
    ui->listfilesRadioButton->setChecked(true);

    m_treeModel = new FileStatModel(this);
    m_treeModel->setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
    ui->filesTreeView->setModel(m_treeModel);
    ui->filesTreeView->header()->setSectionResizeMode(QHeaderView::Stretch);

    m_tableModel = new FileStatModel(this);
    m_tableModel->setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
    ui->filesTableView->setModel(m_tableModel);
    ui->filesTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->filesTreeView->selectionModel(), &QItemSelectionModel::currentRowChanged
            , [this](const QModelIndex &current, const QModelIndex &/*previous*/) {
        handleTreeSelection(current);
    });

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
