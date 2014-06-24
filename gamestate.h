#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "defs.h"
#include <vector>

class GameState
{
public:
    GameState(const size_t numDays, const size_t numHumans);

    State getHumanState(human_t const& human, day_t const& day) const;
    meetings_t getMeetings(human_t const& human, day_t const& day) const;
    size_t getNumDays() const;
    size_t getNumHumans() const;
    void setGameState(human_t const& human, day_t const& day, State state);

private:
    bool checkDimensions(const human_t& human, const day_t& day) const;

private:
    typedef std::vector<std::vector<State> > StateMatrix;
    StateMatrix m_stateMatrix;
};

#endif // GAMESTATE_H
