#include "gamesession.h"

#include "gamestate.h"
#include "guessresponse.h"
#include <QDebug>
#include <QString>
namespace
{
    bool isReady(GameState const& gameState)
    {
        for (auto human : constants::HUMANS)
        {
            if(ILL == gameState.getHumanState(human,Day(0)))
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
    struct SingleGame
    {
      SingleGame(QVector<AbstractClient*> players, Server& server);
      void start();

      QVector<std::pair<AbstractClient*, GameState> > m_playerStates;
      Server& m_server;
      uint16_t m_numRounds;
      QVector<AbstractClient*> m_winners;
    };
}
void GameSession::addPlayer(AbstractClient *player)
{
    Q_ASSERT(0 != player);
    Q_ASSERT(!contains_if(m_players, [&](AbstractClient const* p)
    {
      return p->getName() == player->getName();
    }));
    m_players.push_back(player);
}

void GameSession::start()
{
    Q_ASSERT(!m_players.empty());
    GameState gameState = m_server.generateGame();
    std::vector<GameState> gameStates(m_players.size(), gameState);
    size_t count = 0;
    for ( auto & client : m_players)
    {
        client->tellCurrentState(gameState);
    }
    bool readyFlag = false;
    while(!readyFlag)
    {
        size_t c = 0;
        for ( auto const& client : m_players)
        {
            auto guessResponse = client->guess();
            if(guessResponse.isFinalGuess())
            {
                auto finalGuess = guessResponse.getFinalGuess();

                while(gameStates[c].getHumanState(finalGuess, Day(0)) != ILL &&
                      gameStates[c].getHumanState(finalGuess, Day(0)) != NOT_ILL)
                {
                    m_server.discoverHuman(gameStates[c], finalGuess);
                }
                const auto statusOnTheFirstDay = gameStates[c].getHumanState(finalGuess, Day(0));
                if ( statusOnTheFirstDay == NOT_ILL)
                {
                    client->tellGameResult(false);
                }
                else if (statusOnTheFirstDay == ILL)
                {
                    client->tellGameResult(true);
                    readyFlag = true;
                }
                else
                  {
                    Q_ASSERT(false);
                  }

            }
            else
            {
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
        }
       ++count;
    }
    qDebug() << "Num Steps " << count;
    QString winners;
    for(int c = 0; c < m_players.size(); ++c)
    {
        if(isReady(gameStates[c]))
        {
            winners.append(m_players[c]->getName()).append(" ");
            m_players[c]->tellGameResult(true);
        }
        else
        {
            m_players[c]->tellGameResult(false);
        }
    }
    qDebug() <<" The winners are " << winners;
}


SingleGame::SingleGame(QVector<AbstractClient *> players, Server &server)
  : m_server(server)
  , m_numRounds(0)
{
  for(auto p : players)
  {
    m_playerStates.push_back(std::make_pair(p, GameState()));
    }
}

void SingleGame::start()
{
  bool readyFlag = false;
  std::list<AbstractClient*> loosers;
  while(!readyFlag)
  {
      for ( auto& psIter : m_playerStates)
      {
          AbstractClient* player = psIter.first;
          if(contains(loosers, player))
          {
              continue;
          }
          GameState& state = psIter.second;
          auto const& guessResponse = player->guess();
          if(guessResponse.isFinalGuess())
          {
              auto finalGuess = guessResponse.getFinalGuess();

              while(state.getHumanState(finalGuess, Day(0)) != ILL &&
                    state.getHumanState(finalGuess, Day(0)) != NOT_ILL)
              {
                  m_server.discoverHuman(state, finalGuess);
              }
              const auto statusOnTheFirstDay = state.getHumanState(finalGuess, Day(0));
              Q_ASSERT(statusOnTheFirstDay == NOT_ILL || statusOnTheFirstDay == ILL);
              if (statusOnTheFirstDay == ILL)
              {
                  readyFlag = true;
                  m_winners.push_back(player);
              }
              else
              {
                loosers.push_back(player);
              }
          }
          else
          {
              auto guessedHumans = guessResponse.getRegularGuess();
              Q_ASSERT(!guessedHumans.empty());
              auto nextGuess = *(pickRandom(guessedHumans.begin(), guessedHumans.end()));
              m_server.discoverHuman(state, nextGuess);
              player->tellCurrentState(state);
              if (isReady(state))
              {
                  readyFlag = true;
                  m_winners.push_back(player);
              }
          }
      }
  }
  // todo tell result to winners
}
