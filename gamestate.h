#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "defs.h"
#include <vector>

class GameState
{
public:
    GameState();

    State getHumanState(Human const human, Day const day) const;
    meetings_t getMeetings(Human const human, Day const day) const;
    meetings_t getMeetings(Day const day) const;
    void setGameState(Human const human, Day const day, State state, meetings_t const& meetings);

private:
    bool checkDimensions(const Human human, const Day day) const;

private:
    typedef std::vector<std::vector<State> > StateMatrix;
    StateMatrix m_stateMatrix;
    typedef std::vector<meetings_t> Meetings;
    Meetings m_meetings;
};

#endif // GAMESTATE_H
