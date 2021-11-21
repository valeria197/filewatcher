#ifdef GUI_VERSION
    #include <QApplication>
#else
    #include <QCoreApplication>
    #include <QDebug>
#endif

#ifndef GUI_VERSION

#include <QSharedPointer>
#include <QFileInfo>
#include <QDir>

#include "listfilestrategy.h"
#include "groupfilestrategy.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

#if 1
    QSharedPointer<AbstractDirectoryStrategy> strategy = QSharedPointer<ListFileStrategy>::create();

    const QString currentDir = QDir::currentPath();
    auto info = strategy->getDirectoryInfo(currentDir);
    for (const auto& item : info.keys()) {
        qDebug() << QFileInfo(item).fileName() << " : " << info[item];
    }
    return a.exec();
#else
    QSharedPointer<AbstractDirectoryStrategy> strategy = QSharedPointer<GroupFileStrategy>::create();

    const QString currentDir = QDir::currentPath();
    auto info = strategy->getDirectoryInfo(currentDir + "/..");
    for (const auto& item : info.keys()) {
        qDebug() << item << " : " << info[item];
    }
    return a.exec();
#endif
}
#else // --------------------------------------------------------------

#include "directorystatsmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    DirectoryStatsMainWindow wnd;
    wnd.show();
    return app.exec();
}
#endif
