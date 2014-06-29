#include "gamesession.h"

#include "gamestate.h"
#include <QDebug>
#include <QString>
namespace
{
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
}
void GameSession::addClient(const AbstractClient *client)
{
    Q_ASSERT(0 != client);
    m_clients.append(client);
}

void GameSession::start()
{
    Q_ASSERT(!m_clients.empty());
    GameState gameState = m_server.generateGame();
    size_t count = 0;
    auto bot = m_clients.front();
    while(!isReady(gameState))
    {
        auto guessSet = bot->guess(gameState);
        Q_ASSERT(!guessSet.empty());
        auto nextGuess = *(pickRandom(guessSet.begin(), guessSet.end()));
        qDebug()<< "Next guess " << nextGuess << " from " << containerToString(guessSet) ;
        m_server.discoverHuman(gameState, nextGuess);
        ++count;
    }
    qDebug() << "Num Steps " << count;
}
