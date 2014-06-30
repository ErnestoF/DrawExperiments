#ifndef RANDOMCLIENT_H
#define RANDOMCLIENT_H

#include "abstractclient.h"
class RandomClient : public AbstractClient
{
public:
    RandomClient(QString const& name );

    std::set<human_t> guess(GameState const& gameState) const override;

};

#endif // RANDOMCLIENT_H
