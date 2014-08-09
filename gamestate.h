#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "defs.h"
#include <vector>

class GameState
{
public:
    GameState();

    State getHumanState(Human const human, Day const day) const;
    meetings_t getMeetings() const;
    void setGameState(Human const human, Day const day, State state, meetings_t const& meetings);

private:
    typedef std::vector<std::vector<State> > StateMatrix;
    StateMatrix m_stateMatrix;
    meetings_t m_meetings;
};

#endif // GAMESTATE_H
