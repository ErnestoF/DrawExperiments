#include "gamestate.h"

#include <QString>

using namespace constants;
GameState::GameState()
    : m_stateMatrix(NUM_DAYS, std::vector<State>(NUM_HUMANS, NOT_REQUESTABLE))
{
    m_stateMatrix[NUM_DAYS - 1] = std::vector<State>(NUM_HUMANS, REQUESTABLE);
}

State GameState::getHumanState(const Human human, const Day day) const
{
  return m_stateMatrix[day][human];
}

void GameState::setMeetings(const meetings_t &meetings)
{
  m_meetings = meetings;
}

meetings_t GameState::getMeetings() const
{
  return m_meetings;
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
    for (Meeting const& m : meetings)
    {
        if(!contains(m_meetings, m))
        {
            m_meetings.push_back(m);
        }
    }
}


void GameState::setHumanState(const Human human, const Day day, const State state)
{
  Q_ASSERT(isOneOf(state, ILL, NOT_ILL));
  Q_ASSERT(REQUESTABLE == getHumanState(human, day));
  m_stateMatrix[day][human] = state;
  if(day > 0)
  {
      m_stateMatrix[day - 1][human] = REQUESTABLE;
  }

}
