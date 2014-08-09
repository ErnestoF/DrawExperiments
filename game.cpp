#include "game.h"

#include <chrono>
#include <random>
namespace
{
    meeting_t generateMeeting(const size_t numHumans)
    {
        meeting_t meeting;
        std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<uint8_t> distribution(0,numHumans-1);
        std::uniform_int_distribution<uint8_t> meetingsDistribution(2,5);
        const size_t numParticipants = meetingsDistribution(generator);
        while(static_cast<size_t>(meeting.size()) < numParticipants)
        {
            meeting.insert(Human(distribution(generator)));
        }
        return meeting;
    }

    Game::meetings_table_t generateMeetingsTable(const size_t numHumans, const size_t numDays)
    {
        Q_ASSERT(numDays > 2);
        auto result = Game::meetings_table_t(numDays, meetings_t());
        for (size_t d = 0; d < numDays-1; ++d )
        {
            result[d]<<generateMeeting(numHumans)<<generateMeeting(numHumans);
        }
        return result;
    }
}
using constants::NUM_HUMANS;
using constants::NUM_DAYS;
Game::Game()
  : m_contagionTable(NUM_DAYS, QVector<bool>(NUM_HUMANS, false))
  , m_meetingsTable(generateMeetingsTable(NUM_HUMANS, NUM_DAYS))
{
}

bool Game::isInfected(const Day day, const Human human) const
{
   return m_contagionTable[day][human];
}

meetings_t Game::meetings(const Day day, const Human human) const
{
    meetings_t result;
    for(auto m : m_meetingsTable[day])
    {
        if (m.contains(human))
        {
            result.append(m);
        }
    }
    return result;
}

meetings_t Game::meetings(const Day day) const
{
    return m_meetingsTable[day];
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
    result.m_meetingsTable = generateMeetingsTable(NUM_HUMANS, NUM_DAYS);
    for(uint8_t d(0); d < NUM_DAYS - 1; ++d)
    {
        for(uint8_t h = 0; h < NUM_HUMANS; ++h)
        {
            if (0 < d )
            {
                result.m_contagionTable[d][h] |= result.m_contagionTable[d-1][h];
            }
        }
        for(auto m : result.m_meetingsTable[d])
        {
            size_t numInfected = 0;
            for (auto h : m)
            {
                if (result.isInfected(Day(d),Human(h)))
                {
                    ++numInfected;
                }
            }
            const size_t totalNumber = m.size();
            for (auto h : m)
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
