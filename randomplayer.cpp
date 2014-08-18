#include "randomplayer.h"
#include "gamestate.h"
#include "guessresponse.h"
RandomPlayer::RandomPlayer(const QString &name)
    : AbstractPlayer(name)
    , m_currentState()
{
}

GuessResponse RandomPlayer::guess() const
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

void RandomPlayer::tellCurrentState(const GameState &gameState)
{
    m_currentState = gameState;
}
