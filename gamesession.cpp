#include "gamesession.h"

#include "gamestate.h"
#include "guessresponse.h"
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
void GameSession::addClient(AbstractClient *client)
{
    Q_ASSERT(0 != client);
    m_clients.push_back(client);
}

void GameSession::start()
{
    Q_ASSERT(!m_clients.empty());
    GameState gameState = m_server.generateGame();
    std::vector<GameState> gameStates(m_clients.size(), gameState);
    size_t count = 0;
    for ( auto & client : m_clients)
    {
        client->tellCurrentState(gameState);
    }
    bool readyFlag = false;
    while(!readyFlag)
    {
        size_t c = 0;
        for ( auto const& client : m_clients)
        {
            auto guessResponse = client->guess(false);
            auto guessedHumans = guessResponse.getRegularGuess();
            Q_ASSERT(!guessedHumans.empty());
            auto nextGuess = *(pickRandom(guessedHumans.begin(), guessedHumans.end()));
            m_server.discoverHuman(gameStates[c], nextGuess);
            client->tellCurrentState(gameStates[c]);
            if (isReady(gameStates[c]))
            {
                readyFlag = true;
            }
            ++c;
        }
       ++count;
    }
    qDebug() << "Num Steps " << count;
    QString winners;
    for(int c = 0; c < m_clients.size(); ++c)
    {
        if(isReady(gameStates[c]))
        {
            winners.append(m_clients[c]->getName()).append(" ");
            m_clients[c]->tellGameResult(true);
        }
        else
        {
            m_clients[c]->tellGameResult(false);
        }
    }
    qDebug() <<" The winners are " << winners;
}
