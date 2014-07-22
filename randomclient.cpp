#include "randomclient.h"
#include "gamestate.h"
RandomClient::RandomClient(const QString &name)
    : AbstractClient(name)
    , m_currentState(constants::NUM_DAYS, constants::NUM_HUMANS)
{
}

std::set<human_t> RandomClient::guess() const
{
    std::set<human_t> result;
    for(human_t h = 0; h < m_currentState.getNumHumans(); ++h)
    {
        if (m_currentState.getHumanState(h,0) == REQUESTABLE ||  m_currentState.getHumanState(h,0) == NOT_REQUESTABLE)
        {
            result.insert(h);
        }
    }
    return result;
}

void RandomClient::tellCurrentState(const GameState &gameState)
{
    m_currentState = gameState;
}
