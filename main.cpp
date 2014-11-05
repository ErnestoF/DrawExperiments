#include <boost/python.hpp>
#undef B0
#include "gamesession.h"
#include "guiplayer.h"
#include "mainwindow.h"
#include "randomplayer.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);
    Py_Initialize();
    QApplication a(argc, argv);

    GuiPlayer guiClient("GuiClient");

    GameSession session;
    RandomPlayer client1("RandomBot1");
    RandomPlayer client2("RandomBot2");
    RandomPlayer client3("RandomBot3");
    RandomPlayer client4("RandomBot4");
    RandomPlayer client5("RandomBot5");
    session.addPlayer(&client1);
    session.addPlayer(&client2);
    session.addPlayer(&client3);
    session.addPlayer(&client4);
    session.addPlayer(&client5);
    session.addPlayer(&guiClient);
    session.start();
    return a.exec();
}
