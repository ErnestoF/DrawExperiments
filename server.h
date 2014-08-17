#ifndef SERVER_H
#define SERVER_H

#include "defs.h"
#include <memory>

class GameState;

class Server
{
public:
    Server() = default;
    GameState generateGame();
    void discoverHuman(GameState& gameState, Human const human) const;

private: // Methods

    Server(const Server&) = delete;
    Server & operator=(const Server&) = delete;

private: // Attributes
    class Game;
    std::shared_ptr<Game> m_game;
};

#endif // SERVER_H
