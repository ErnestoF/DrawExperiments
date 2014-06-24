#ifndef SERVER_H
#define SERVER_H

#include "defs.h"
#include <memory>

class GameState;
class Game;

class Server
{
public:
    Server();

    GameState generateGame();

    void discoverHuman(GameState& gameState, human_t const& human) const;

private:

    std::shared_ptr<Game> m_game;
};

#endif // SERVER_H
