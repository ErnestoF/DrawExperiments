#ifndef ABSTRACTCLIENT_H
#define ABSTRACTCLIENT_H

#include "defs.h"
#include <set>

class GameState;

class AbstractClient
{
   virtual std::set<human_t> guess(GameState const& gameState) const = 0;
};

#endif // ABSTRACTCLIENT_H
