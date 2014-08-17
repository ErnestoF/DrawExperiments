#include "gamesession.h"
#include "guiclient.h"
#include "mainwindow.h"
#include "randomclient.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    QApplication a(argc, argv);

    GuiClient guiClient("GuiClient");

    GameSession session;
    RandomClient client1("RandomBot1");
    RandomClient client2("RandomBot2");
    RandomClient client3("RandomBot3");
    RandomClient client4("RandomBot4");
    RandomClient client5("RandomBot5");
    session.addPlayer(&client1);
    session.addPlayer(&client2);
    session.addPlayer(&client3);
    session.addPlayer(&client4);
    session.addPlayer(&client5);
    session.addPlayer(&guiClient);
    session.start();
    return a.exec();
    //return 0;
}
