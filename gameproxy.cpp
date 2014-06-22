#include "gameproxy.h"

GameProxy::GameProxy(Game const& game)
    : m_game(game)
    , visibilityMatrix(m_game.numDays(), std::vector<bool>(m_game.numHumans(), false))
{

}

State GameProxy::getHumanState() const
{
    return NOT_REQUESTABLE;
}
