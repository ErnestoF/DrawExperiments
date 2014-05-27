#include "game.h"

#include <chrono>
#include <random>
#include <iostream> // todo remove
namespace
{
    Game::meeting_t generateMeeting(const size_t numHumans, const size_t numParticipants)
    {
        Game::meeting_t meeting;
        std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<Game::human_t> distribution(0,numHumans-1);
        while(static_cast<size_t>(meeting.size()) < numParticipants)
        {
            generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
            meeting.insert(distribution(generator));
        }
        return meeting;
    }
}
Game::Game(const human_t numHumans, const day_t numDays) :
    m_numDays(numDays)
  , m_numHumans(numHumans)
  , m_contagionTable(numDays, QVector<bool>(numHumans, false))
  , m_meetingsTable(numDays, meetings_t())
{
}

size_t Game::numDays() const
{
    return m_numDays;
}

size_t Game::numHumans() const
{
    return m_numHumans;
}

bool Game::isInfected(const day_t day, const human_t human) const
{
    Q_ASSERT(day < numDays());
    Q_ASSERT(human < numHumans());

    return m_contagionTable[day][human];
}

Game::meetings_t Game::meetings(const day_t day, const human_t human) const
{
    Q_ASSERT(day < numDays());
    Q_ASSERT(human < numHumans());
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

Game::meetings_t Game::meetings(const Game::day_t day) const
{
    Q_ASSERT(day < numDays());
    return m_meetingsTable[day];
}

Game Game::generateGame(const human_t numHumans, const day_t numDays)
{
    Q_ASSERT(0 < numHumans);
    Q_ASSERT(1 < numDays);
    Game result(numHumans, numDays);
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<human_t> distribution(0,numHumans);
    std::uniform_int_distribution<size_t> meetingsDistribution(2,5);
    std::uniform_real_distribution<float> infectionDistribution;
    const human_t firstInfectedHuman = distribution(generator);
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    result.m_contagionTable[0][firstInfectedHuman] = true;

    for(day_t d = 1; d < result.numDays()-1; ++d)
    {
        for(human_t h = 0; h < result.numHumans(); ++h)
        {
            result.m_contagionTable[d][h] |= result.m_contagionTable[d-1][h];
        }
        generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
        const size_t meeting1Count = meetingsDistribution(generator);
        result.m_meetingsTable[d].push_back(generateMeeting(result.numHumans(), meeting1Count));
        generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
        const size_t meeting2Count = meetingsDistribution(generator);
        result.m_meetingsTable[d].push_back(generateMeeting(result.numHumans(),meeting2Count));
        std::cout<<"Meeting at day " << d << "\n";
        for(auto m : result.m_meetingsTable[d])
        {
            for(auto h : m)
            {
                std::cout << h <<" ";
            }
            std::cout<<"\n";
        }
        for(auto m : result.m_meetingsTable[d])
        {
            size_t numInfected = 0;
            for (auto h : m)
            {
                if (result.isInfected(d,h))
                {
                    ++numInfected;
                }
            }
            const size_t totalNumber = m.size();
            for (auto h : m)
            {
                if(!result.isInfected(d,h))
                {
                    result.m_contagionTable[d+1][h] = infectionDistribution(generator) < (numInfected/static_cast<float>(totalNumber));
                }
            }
        }
    }
    for(size_t h = 0; h < result.numHumans(); ++h)
    {
        Q_ASSERT(result.numDays() >=2);
         result.m_contagionTable[result.numDays()-1][h] |= result.m_contagionTable[result.numDays()-2][h];
    }

    return result;

}
