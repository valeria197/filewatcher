#ifndef DIRECTORYSTATSMAINWINDOW_H
#define DIRECTORYSTATSMAINWINDOW_H

#include <QWidget>

namespace Ui {
class DirectoryStatsMainWindow;
}

QT_FORWARD_DECLARE_CLASS(QModelIndex)
class AbstractDirectoryStrategy;
class FileStatModel;

class DirectoryStatsMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DirectoryStatsMainWindow(QWidget *parent = nullptr);
    ~DirectoryStatsMainWindow();

private:
    void chooseTreeFolder(const QString &path);
    void handleTreeSelection(const QModelIndex &index);

private:
    const QSharedPointer<Ui::DirectoryStatsMainWindow> ui;
    FileStatModel *m_treeModel;
    FileStatModel *m_tableModel;

    QSharedPointer<AbstractDirectoryStrategy> fileStatStrategy;
    QSharedPointer<AbstractDirectoryStrategy> fileGroupStatStrategy;
};

#endif // DIRECTORYSTATSMAINWINDOW_H
