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
    RandomClient client1("RandomBot1");
    RandomClient client2("RandomBot2");
    RandomClient client3("RandomBot3");
    RandomClient client4("RandomBot4");
    RandomClient client5("RandomBot5");
    session.addClient(&client1);
    session.addClient(&client2);
    session.addClient(&client3);
    session.addClient(&client4);
    session.addClient(&client5);
    session.start();
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    //return a.exec();
    return 0;
}
