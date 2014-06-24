#include "server.h"

#include "game.h"
#include "gamestate.h"
namespace
{
const size_t NUM_HUMANS = 10;
const size_t NUM_DAYS = 10;
}

Server::Server()
{
}

GameState Server::generateGame()
{
    m_game.reset(new Game(Game::generateGame(NUM_HUMANS, NUM_DAYS)));
    return GameState(NUM_DAYS, NUM_HUMANS);
}

void Server::discoverHuman(GameState &gameState, const human_t &human) const
{
    Q_UNUSED(gameState);
    Q_UNUSED(human);
    // todo implement
}
