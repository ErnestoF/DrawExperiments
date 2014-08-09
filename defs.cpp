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
