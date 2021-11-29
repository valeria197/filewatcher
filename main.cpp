#include <QApplication>
#include <QSharedPointer>
#include <QFileInfo>
#include <QDir>

#include "statsmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    StatsMainWindow wnd;
    wnd.show();
    return app.exec();
}
