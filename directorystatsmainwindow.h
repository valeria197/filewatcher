#ifndef DIRECTORYSTATSMAINWINDOW_H
#define DIRECTORYSTATSMAINWINDOW_H

#include <QWidget>

namespace Ui {
class DirectoryStatsMainWindow;
}

class FileStatModel;
class QModelIndex;

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
};

#endif // DIRECTORYSTATSMAINWINDOW_H
