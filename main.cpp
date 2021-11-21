#include <QApplication>
#include <QSharedPointer>
#include <QFileInfo>
#include <QDir>

#include "directorystatsmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    DirectoryStatsMainWindow wnd;
    wnd.show();
    return app.exec();
}
