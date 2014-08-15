#include "server.h"
#include "gamestate.h"

#include <QVector>
#include <chrono>
using namespace constants;
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
    Meeting generateMeeting(Day d)
    {
        std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<uint8_t> distribution(0,NUM_HUMANS - 1 );
        std::uniform_int_distribution<uint8_t> meetingsDistribution(2,5);
        std::set<Human> participants;

        const uint8_t numParticipants = meetingsDistribution(generator);
        while(static_cast<size_t>(participants.size()) < numParticipants)
        {
            participants.insert(Human(distribution(generator)));
        }
        return Meeting(d, participants);
    }
    meetings_t generateMeetings()
    {
        meetings_t result;
        for(auto d : DAYS)
        {
            if(d != NUM_DAYS - 1)
            {
                result.push_back(generateMeeting(d));
                result.push_back(generateMeeting(d));
            }
        }
        return result;
    }
    meetings_t meetingsOnDay(meetings_t const& allMeetings, Day d)
    {
        meetings_t result;
        std::copy_if(std::begin(allMeetings),
                     std::end(allMeetings),
                     std::back_inserter(result),
                     [=](Meeting const& m) {return m.day() == d;});
        return result;
    }
    Human generateFirstInfectedHuman()
    {
        std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<uint8_t> distribution(0,NUM_HUMANS - 1);
        return Human(distribution(generator));
    }
}

class Server::Game
{
public:
    Game();

    bool isInfected(const Day day, const Human human) const;
    meetings_t meetings() const;
    static Game generateGame();
private:
    void propagateStatusToTheNextDay(const Day day);
    QVector<QVector<bool> > m_contagionTable;
    meetings_t m_meetings;
};

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

Server::Game::Game()
  : m_contagionTable(NUM_DAYS, QVector<bool>(NUM_HUMANS, false))
{
}

bool Server::Game::isInfected(const Day day, const Human human) const
{
   return m_contagionTable[day][human];
}

meetings_t Server::Game::meetings() const
{
    return m_meetings;
}

Server::Game Server::Game::generateGame()
{
    Game result;
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<float> infectionDistribution;
    result.m_contagionTable[0][generateFirstInfectedHuman()] = true;
    result.m_meetings = generateMeetings();
    for(uint8_t d(0); d < NUM_DAYS - 1; ++d)
    {
        result.propagateStatusToTheNextDay(Day(d));
        for(auto m : meetingsOnDay(result.meetings(), Day(d)))
        {
            size_t numInfected = 0;
            for (auto h : m.participants())
            {
                if (result.isInfected(Day(d),Human(h)))
                {
                    ++numInfected;
                }
            }
            const size_t totalNumber = m.participants().size();
            for (auto h : m.participants())
            {
                if(!result.isInfected(Day(d),Human(h)))
                {
                    result.m_contagionTable[d+1][h] = infectionDistribution(generator) < (numInfected/static_cast<float>(totalNumber));
                }
            }
        }
    }
    result.propagateStatusToTheNextDay(Day(NUM_DAYS-1));
    return result;

}

void Server::Game::propagateStatusToTheNextDay(const Day day)
{
    for(auto h : HUMANS)
    {
        if (0 < day )
        {
            m_contagionTable[day][h] |= m_contagionTable[day-1][h];
        }
    }
}
