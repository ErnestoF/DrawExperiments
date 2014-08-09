#ifndef SERVER_H
#define SERVER_H

#include "defs.h"
#include "game.h"
#include <memory>

class GameState;
class Game;

class Server
{
public:

    GameState generateGame();

    void discoverHuman(GameState& gameState, Human const human) const;

private:

    std::unique_ptr<Game> m_game;
};

#endif // SERVER_H
