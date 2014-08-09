#include "defs.h"

namespace
{
std::vector<Human> calcHumans()
{
    std::vector<Human> result;
    for(uint8_t id = 0; id < constants::NUM_HUMANS; ++id)
    {
        result.push_back(Human(id));
    }
    return result;
}

std::vector<Day> calcDays()
{
    std::vector<Day> result;
    for(uint8_t id = 0; id < constants::NUM_DAYS; ++id)
    {
        result.push_back(Day(id));
    }
    return result;
}

}

const std::vector<Human> constants::HUMANS = calcHumans();

const std::vector<Day> constants::DAYS = calcDays();


Meeting::Meeting(Day d, std::set<Human> humans)
    : m_day(d)
    , m_humans(humans)
{}

Day Meeting::day() const
{
    return m_day;
}

std::set<Human> Meeting::humans() const
{
    return m_humans;
}

bool Meeting::operator==(const Meeting &other) const
{
    return m_day == other.day() && m_humans == other.humans();
}
