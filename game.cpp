#include "game.h"

#include <chrono>
#include <random>
using namespace constants;
namespace
{
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
}
Game::Game()
  : m_contagionTable(NUM_DAYS, QVector<bool>(NUM_HUMANS, false))
{
}

bool Game::isInfected(const Day day, const Human human) const
{
   return m_contagionTable[day][human];
}

meetings_t Game::meetings() const
{
    return m_meetings;
}

Game Game::generateGame()
{
    Game result;
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<uint8_t> distribution(0,NUM_HUMANS - 1);
    std::uniform_real_distribution<float> infectionDistribution;
    const Human firstInfectedHuman(distribution(generator));
    Q_ASSERT(firstInfectedHuman < NUM_HUMANS);
    result.m_contagionTable[0][firstInfectedHuman] = true;
    result.m_meetings = generateMeetings();
    for(uint8_t d(0); d < NUM_DAYS - 1; ++d)
    {
        for(uint8_t h = 0; h < NUM_HUMANS; ++h)
        {
            if (0 < d )
            {
                result.m_contagionTable[d][h] |= result.m_contagionTable[d-1][h];
            }
        }
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
    for(uint8_t h = 0; h < NUM_HUMANS; ++h)
    {
        result.m_contagionTable[NUM_DAYS-1][h] |= result.m_contagionTable[NUM_DAYS-2][h];
    }

    return result;

}
