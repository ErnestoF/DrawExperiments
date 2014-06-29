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

template <typename IteratorT>
IteratorT pickRandom(IteratorT from, IteratorT to)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, std::distance(from, to) - 1);
    std::advance(from, dis(gen));
    return from;
}

template <typename Container>
QString containerToString(Container const& container)
{
    QString result;
    for (auto elem : container)
    {
        result.append(QString::number(elem)).append(" ");
    }
    return result;
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
        auto guessSet = bot.guess(gameState);
        Q_ASSERT(!guessSet.empty());
        auto nextGuess = *(pickRandom(guessSet.begin(), guessSet.end()));
        qDebug()<< "Next guess " << nextGuess << " from " << containerToString(guessSet) ;
        server.discoverHuman(gameState, nextGuess);
        ++count;
    }
    qDebug() << "Num Steps " << count;
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    //return a.exec();
    return 0;
}
