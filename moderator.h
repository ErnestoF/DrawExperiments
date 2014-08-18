#pragma once

#include "defs.h"
#include <memory>

class GameState;

class Moderator
{
public:
    Moderator() = default;
    GameState generateGame();
    void discoverHuman(GameState& gameState, Human const human) const;

private: // Methods

    Moderator(const Moderator&) = delete;
    Moderator & operator=(const Moderator&) = delete;

private: // Attributes
    class Game;
    std::shared_ptr<Game> m_game;
};
