#include "gamestate.h"

#include <QString>

GameState::GameState(const size_t numDays, const size_t numHumans)
    : m_stateMatrix(numDays, std::vector<State>(numHumans, NOT_REQUESTABLE))
    , m_meetings(numDays, meetings_t())
{
    Q_ASSERT(numDays > 2);
    m_stateMatrix[numDays - 1] = std::vector<State>(numHumans, REQUESTABLE);
}

State GameState::getHumanState(const human_t &human, const day_t &day) const
{
    Q_ASSERT_X(checkDimensions(human, day), "GameState::getHumanState", QString("Human ").append(QString::number(human).append(" Day ").append(QString::number(day))).toLocal8Bit().data());
    return m_stateMatrix[day][human];
}

meetings_t GameState::getMeetings(const human_t &human, const day_t &day) const
{
    Q_ASSERT(checkDimensions(human, day));
    auto meetingsOnDay = m_meetings[day];
    meetings_t result;
    for ( auto m : meetingsOnDay)
    {
        if (m.contains(human))
        {
            result.append(m);
        }
    }
    return result;
}

meetings_t GameState::getMeetings(const day_t &day) const
{
    Q_ASSERT(0 <= day && day < getNumDays());
    return m_meetings[day];
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

void GameState::setGameState(const human_t &human, const day_t &day, State state, meetings_t const& meetings)
{
    Q_ASSERT(NOT_REQUESTABLE != state && REQUESTABLE != state);
    Q_ASSERT(checkDimensions(human, day));
    Q_ASSERT(REQUESTABLE == getHumanState(human, day));
    m_stateMatrix[day][human] = state;
    if(day > 0)
    {
        m_stateMatrix[day - 1][human] = REQUESTABLE;
    }
    for (auto m : meetings)
    {
        if (!m_meetings[day].contains(m))
        {
            m_meetings[day].append(m);
        }
    }
}

bool GameState::checkDimensions(const human_t &human, const day_t &day) const
{
    return human < getNumHumans() && day < getNumDays();
}
