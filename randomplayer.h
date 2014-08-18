#pragma once

#include "abstractplayer.h"
#include "gamestate.h"
class RandomPlayer : public AbstractPlayer
{
public:
    RandomPlayer(QString const& name);
    GuessResponse guess() const override;
    void tellCurrentState(GameState const& gameState) override;

private:
    GameState m_currentState;
};

