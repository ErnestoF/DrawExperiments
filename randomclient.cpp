#include "randomclient.h"
#include "gamestate.h"
#include "guessresponse.h"
RandomClient::RandomClient(const QString &name)
    : AbstractClient(name)
    , m_currentState()
{
}

GuessResponse RandomClient::guess() const
{
    std::set<Human> result;
    for(auto h : constants::HUMANS)
    {
        if (m_currentState.getHumanState(h,Day(0)) == REQUESTABLE ||  m_currentState.getHumanState(h,Day(0)) == NOT_REQUESTABLE)
        {
            result.insert(h);
        }
    }
    return GuessResponse::makeRegularGuess(result);
}

void RandomClient::tellCurrentState(const GameState &gameState)
{
    m_currentState = gameState;
}
