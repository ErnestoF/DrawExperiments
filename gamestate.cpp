#include "gamestate.h"

#include <QString>

using namespace constants;
GameState::GameState()
    : m_stateMatrix(NUM_DAYS, std::vector<State>(NUM_HUMANS, NOT_REQUESTABLE))
    , m_meetings(NUM_DAYS, meetings_t())
{
    m_stateMatrix[NUM_DAYS - 1] = std::vector<State>(NUM_HUMANS, REQUESTABLE);
}

State GameState::getHumanState(const Human human, const Day day) const
{
    return m_stateMatrix[day][human];
}

meetings_t GameState::getMeetings(const Human human, const Day day) const
{
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

meetings_t GameState::getMeetings(const Day day) const
{
    return m_meetings[day];
}


void GameState::setGameState(const Human human, const Day day, State state, meetings_t const& meetings)
{
    Q_ASSERT(NOT_REQUESTABLE != state && REQUESTABLE != state);
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
