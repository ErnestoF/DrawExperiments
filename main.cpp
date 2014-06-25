#include "mainwindow.h"
#include "randomclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    RandomClient bot;
    return a.exec();
}
// hello world
