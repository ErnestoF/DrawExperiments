#include "gamesession.h"
#include "guiclient.h"
#include "mainwindow.h"
#include "randomclient.h"
#include <QApplication>
#include <QDebug>
#include <QGraphicsView>
int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    QApplication a(argc, argv);

    GuiClient guiClient("GuiClient");
    QGraphicsView view(guiClient.getScene());
    view.show();
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
    session.addClient(&guiClient);
    session.start();

    return a.exec();
    //return 0;
}
