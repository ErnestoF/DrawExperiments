#include "defs.h"
#include "utils.h"

using namespace constants;

const std::array<Human, NUM_HUMANS> constants::HUMANS = createArray<Human, NUM_HUMANS>();

const std::array<Day, NUM_DAYS> constants::DAYS = createArray<Day, NUM_DAYS>();


Meeting::Meeting(Day d, std::set<Human> humans)
    : m_day(d)
    , m_humans(humans)
{}

Day Meeting::day() const
{
    return m_day;
}

std::set<Human> Meeting::participants() const
{
    return m_humans;
}

bool Meeting::operator==(const Meeting &other) const
{
    return m_day == other.day() && m_humans == other.participants();
}
