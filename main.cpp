#include "gamestate.h"
#include "mainwindow.h"
#include "randomclient.h"
#include "server.h"
#include <QApplication>
#include <QDebug>
bool isReady(GameState const& gameState)
{
    for (size_t h = 0; h < gameState.getNumHumans(); ++h)
    {
        if(ILL == gameState.getHumanState(h,0))
        {
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);
    Server server;
    GameState gameState = server.generateGame();
    RandomClient bot;
    size_t count = 0;
    while(!isReady(gameState))
    {
        auto guess = bot.guess(gameState);
        Q_ASSERT(!guess.empty());
        server.discoverHuman(gameState, *guess.begin());
        ++count;
    }
    qDebug() << "Num Steps " << count;
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    //return a.exec();
    return 0;
}
