#define GUI_VERSION

#ifdef GUI_VERSION
    #include <QApplication>
#else
    #include <QCoreApplication>
    #include <QDebug>
#endif

#include <QSharedPointer>
#include <QFileInfo>
#include <QDir>

#include "listfilestrategy.h"
#include "groupfilestrategy.h"

#ifndef GUI_VERSION
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

#if 0
    QSharedPointer<AbstractDirectoryStrategy> strategy = QSharedPointer<ListFileStrategy>::create();

    const QString currentDir = QDir::currentPath();
    for (auto& item : strategy->getDirectoryInfo(currentDir)) {
        qDebug() << QFileInfo(item.first).fileName() << " : " << item.second;
    }
    return a.exec();
#else
    QSharedPointer<AbstractDirectoryStrategy> strategy = QSharedPointer<GroupFileStrategy>::create();

    const QString currentDir = QDir::currentPath();
    for (auto& item : strategy->getDirectoryInfo(currentDir + "/..")) {
        qDebug() << item.first << " : " << item.second;
    }
    return a.exec();
#endif
}
#else // --------------------------------------------------------------

#include "directorystatsmainwindow.h"

//#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    DirectoryStatsMainWindow wnd;
    wnd.show();
    return app.exec();
}
#endif
