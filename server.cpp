#include "server.h"

#include "game.h"
#include "gamestate.h"

Server::Server()
{
}

GameState Server::generateGame()
{
    m_game.reset(new Game(Game::generateGame(constants::NUM_HUMANS, constants::NUM_DAYS)));
    return GameState(constants::NUM_DAYS, constants::NUM_HUMANS);
}

void Server::discoverHuman(GameState &gameState, const human_t &human) const
{
    Q_ASSERT(m_game && m_game->numDays() == gameState.getNumDays() && m_game->numHumans() == gameState.getNumHumans());
    auto numDays = gameState.getNumDays();
    Q_ASSERT(numDays > 1);
    for (size_t d = numDays - 1; ; --d )
    {
        if (REQUESTABLE == gameState.getHumanState(human, d))
        {
            gameState.setGameState(human, d, m_game->isInfected(d,human) ? ILL : NOT_ILL, m_game->meetings(d, human));
            return;
        }
    }
    Q_ASSERT(gameState.getHumanState(human,0) !=     NOT_REQUESTABLE);
}
