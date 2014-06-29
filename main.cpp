#include "gamesession.h"
#include "mainwindow.h"
#include "randomclient.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    GameSession session;
    RandomClient client;
    session.addClient(&client);
    session.start();
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    //return a.exec();
    return 0;
}
