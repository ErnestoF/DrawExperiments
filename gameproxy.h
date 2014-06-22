#ifndef GAMEPROXY_H
#define GAMEPROXY_H

#include "game.h"

class GameProxy
{
public:
    GameProxy(Game const& game);

    State getHumanState() const;
private:
    Game m_game; // todo think how to assure that the server has produced the same game.
    typedef std::vector<std::vector<bool> > visibility_matrix_t;
    visibility_matrix_t visibilityMatrix;
};

#endif // GAMEPROXY_H
