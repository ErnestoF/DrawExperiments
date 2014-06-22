#ifndef GAMEPROXY_H
#define GAMEPROXY_H

#include "game.h"

class GameProxy
{
public:
    GameProxy(Game const& game);

    State getHumanState(human_t const& human, day_t const& day) const;

    void setDiscovered(human_t const& human, day_t const& day);

    meetings_t getMeetings(human_t const& human, day_t const& day) const;
private: // methods

    bool checkDimensions(const human_t& human, const day_t& day) const;
    bool isDiscovered(const human_t& human, const day_t& day) const;
private: // attributes


    Game m_game; // todo think how to assure that the server has produced the same game.
    typedef std::vector<std::vector<bool> > visibility_matrix_t;
    visibility_matrix_t visibilityMatrix;
};

#endif // GAMEPROXY_H
