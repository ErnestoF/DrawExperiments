#include "gameproxy.h"

GameProxy::GameProxy(Game const& game)
    : m_game(game)
    , visibilityMatrix(m_game.numDays() + 1, std::vector<bool>(m_game.numHumans(), false))
{
    visibilityMatrix[m_game.numDays()] = std::vector<bool>(m_game.numHumans(), true);
}

State GameProxy::getHumanState(human_t const& human, day_t const& day) const
{
    Q_ASSERT(checkDimensions(human, day));
    if (isDiscovered(human, day))
    {
        return m_game.isInfected(day, human) ? ILL : NOT_ILL;
    }
    else if (isDiscovered(human, day+1))
    {
        return REQUESTABLE;
    }
    else
    {
    return NOT_REQUESTABLE;
    }
}

void GameProxy::setDiscovered(const human_t &human, const day_t &day)
{
    Q_ASSERT(checkDimensions(human, day));
    Q_ASSERT(isDiscovered(human, day+1));
    visibilityMatrix[day][human] = true;
}

meetings_t GameProxy::getMeetings(const human_t &human, const day_t &day) const
{
    Q_ASSERT(checkDimensions(human, day));
    if(isDiscovered(human, day))
    {
        return m_game.meetings(day, human);
    }
    else
    {
        return meetings_t();
    }
}

bool GameProxy::checkDimensions(const human_t &human, const day_t &day) const
{
    return human < m_game.numHumans() && day < m_game.numDays();
}

bool GameProxy::isDiscovered(const human_t &human, const day_t &day) const
{
    Q_ASSERT(checkDimensions(human, day));
    return visibilityMatrix[day][human];
}
