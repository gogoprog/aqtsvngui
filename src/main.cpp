#include "mainwindow.h"

#include <QtGui>
#include <QApplication>
#include "settings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Settings::getInstance().initialize();
    MainWindow w;
    w.show();
    return a.exec();
}
