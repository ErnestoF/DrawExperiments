#include "gamestate.h"

GameState::GameState(const size_t numDays, const size_t numHumans)
    : m_stateMatrix(numDays, std::vector<State>(numHumans, NOT_REQUESTABLE))
{
    Q_ASSERT(numDays > 2);
    m_stateMatrix[numDays - 1] = std::vector<State>(numHumans, REQUESTABLE);
}

State GameState::getHumanState(const human_t &human, const day_t &day) const
{
    Q_ASSERT(checkDimensions(human, day));
    return m_stateMatrix[day][human];
}

size_t GameState::getNumDays() const
{
    return m_stateMatrix.size();
}

size_t GameState::getNumHumans() const
{
    Q_ASSERT(!m_stateMatrix.empty());
    return m_stateMatrix.front().size();
}

void GameState::setGameState(const human_t &human, const day_t &day, State state)
{
    Q_ASSERT(NOT_REQUESTABLE != state && REQUESTABLE != state);
    Q_ASSERT(checkDimensions(human, day));
    Q_ASSERT(REQUESTABLE == getHumanState(human, day));
    m_stateMatrix[day][human] = state;
    if(day > 0)
    {
        m_stateMatrix[day - 1][human] = REQUESTABLE;
    }
}

bool GameState::checkDimensions(const human_t &human, const day_t &day) const
{
    return human < getNumHumans() && day < getNumDays();
}
