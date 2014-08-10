#include "server.h"
#include "gamestate.h"

namespace
{
    meetings_t meetingsOnDay(meetings_t const& meetings, Day d, Human h)
    {
        meetings_t result;
        std::copy_if(std::begin(meetings),
                     std::end(meetings),
                     std::back_inserter(result),
                     [=](Meeting const& m)
        {
            return (m.day() == d) && contains(m.participants(), h);
        });
        return result;
    }
}

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
            gameState.setGameState(human, Day(d), m_game->isInfected(Day(d),human) ? ILL : NOT_ILL, meetingsOnDay(m_game->meetings(), d, human));
            return;
        }
    }
    Q_ASSERT(gameState.getHumanState(human,Day(0)) != NOT_REQUESTABLE);
}
