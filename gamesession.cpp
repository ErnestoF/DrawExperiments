#include "gamesession.h"

#include "defs.h"
#include "gamestate.h"
#include "guessresponse.h"
#include "utils.h"

#include <random>
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

void tellGameResults( QVector<AbstractPlayer*> const& allPlayers,
                      QVector<AbstractPlayer*> const& winners)
{
    QString winnersStr;
    for(AbstractPlayer* p : allPlayers)
    {
        if(contains(winners, p))
        {
            winnersStr.append(p->getName()).append(" ");
            p->tellGameResult(true);
        }
        else
        {
            p->tellGameResult(false);
        }
    }
    qDebug() <<" The winners are " << winnersStr;
}
struct SingleGame
{
    SingleGame(QVector<AbstractPlayer*> players, Moderator& server);
    typedef QVector<std::pair<AbstractPlayer*, GameState> > PlayerStates;
    PlayerStates m_playerStates;
    Moderator& m_server;
    uint16_t m_numRounds;
    QVector<AbstractPlayer*> m_winners;
    QVector<AbstractPlayer*> m_loosers;
private:
    void start();
    bool askPlayer(PlayerStates::reference playerState);
    State discoverTillFirstDay(GameState& gameState, Human h);

};
}
void GameSession::addPlayer(AbstractPlayer *player)
{
    Q_ASSERT(0 != player);
    Q_ASSERT(!contains_if(
                 m_players,
                 [&](AbstractPlayer const* p){return p->getName() == player->getName();}));
    m_players.push_back(player);
}

void GameSession::start()
{
    Q_ASSERT(!m_players.empty());
    SingleGame singleGame(m_players, m_server);
    qDebug() << "Rounds count " << singleGame.m_numRounds;
    tellGameResults(m_players, singleGame.m_winners);
}


SingleGame::SingleGame(QVector<AbstractPlayer *> players, Moderator &server)
    : m_server(server)
    , m_numRounds(0)
{
    auto gameState = server.generateGame();
    for(AbstractPlayer* p : players)
    {
        GameState initialState = gameState;
        m_playerStates.push_back(std::make_pair(p, initialState));
        p->tellCurrentState(initialState);
    }
    start();
}

void SingleGame::start()
{
    bool readyFlag = false;
    while(!readyFlag)
    {
        ++m_numRounds;
        for ( auto& it : m_playerStates)
        {
            readyFlag |= askPlayer(it);
        }
    }
}

bool SingleGame::askPlayer(PlayerStates::reference playerState)
{
    AbstractPlayer* player = playerState.first;
    GameState& state = playerState.second;
    if(contains(m_loosers, player))
    {
        return false;
    }
    auto const& guessResponse = player->guess();
    if(guessResponse.isFinalGuess())
    {
        auto finalGuess = guessResponse.getFinalGuess();
        const auto statusOnTheFirstDay = discoverTillFirstDay(state, finalGuess);
        Q_ASSERT(statusOnTheFirstDay == NOT_ILL || statusOnTheFirstDay == ILL);
        if (statusOnTheFirstDay == ILL)
        {
            m_winners.push_back(player);
            return true;
        }
        else
        {
            m_loosers.push_back(player);
            return false;
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
            m_winners.push_back(player);
            return true;
        }
        return false;
    }
}

State SingleGame::discoverTillFirstDay(GameState &gameState, Human h)
{
    while(gameState.getHumanState(h, Day(0)) != ILL &&
          gameState.getHumanState(h, Day(0)) != NOT_ILL)
    {
        m_server.discoverHuman(gameState, h);
    }
    return gameState.getHumanState(h, Day(0));
}
