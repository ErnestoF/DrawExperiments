#ifndef RANDOMCLIENT_H
#define RANDOMCLIENT_H

#include "abstractclient.h"
#include "gamestate.h"
class RandomClient : public AbstractClient
{
public:
    RandomClient(QString const& name);
    std::set<human_t> guess() const override;
    void tellCurrentState(GameState const& gameState) override;

private:
    GameState m_currentState;
};

#endif // RANDOMCLIENT_H
