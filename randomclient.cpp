#include "randomclient.h"
#include "gamestate.h"
RandomClient::RandomClient()
{
}

std::set<human_t> RandomClient::guess(const GameState &gameState) const
{
    std::set<human_t> result;
    for(human_t h = 0; h < gameState.getNumHumans(); ++h)
    {
        if (gameState.getHumanState(h,0) == REQUESTABLE ||  gameState.getHumanState(h,0) == NOT_REQUESTABLE)
        {
            result.insert(h);
        }
    }
    return result;
}
