#include "server.h"
#include "gamestate.h"


GameState Server::generateGame()
{
    m_game.reset(new Game(Game::generateGame()));
    return GameState();
}

void Server::discoverHuman(GameState &gameState, const Human human) const
{
    Q_ASSERT(m_game);
    for(auto d: constants::DAYS)
    {
        if (REQUESTABLE == gameState.getHumanState(human, d))
        {
            gameState.setGameState(human, Day(d), m_game->isInfected(Day(d),human) ? ILL : NOT_ILL, m_game->meetings(Day(d), human));
            return;
        }
    }
    Q_ASSERT(gameState.getHumanState(human,Day(0)) != NOT_REQUESTABLE);
}
