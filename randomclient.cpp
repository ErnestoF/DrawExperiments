#include "randomclient.h"
#include "gamestate.h"
#include "guessresponse.h"
RandomClient::RandomClient(const QString &name)
    : AbstractClient(name)
    , m_currentState(constants::NUM_DAYS, constants::NUM_HUMANS)
{
}

GuessResponse RandomClient::guess(bool finalGuessIsMade) const
{
    Q_UNUSED(finalGuessIsMade);
    std::set<human_t> result;
    for(human_t h = 0; h < m_currentState.getNumHumans(); ++h)
    {
        if (m_currentState.getHumanState(h,0) == REQUESTABLE ||  m_currentState.getHumanState(h,0) == NOT_REQUESTABLE)
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
