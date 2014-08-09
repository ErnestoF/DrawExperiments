#pragma once

#include <QSet>
#include <QList>
enum State
{
    NOT_REQUESTABLE, // 0
    REQUESTABLE, // 1
    ILL, // 2
    NOT_ILL // 3
};


namespace constants
{
    const uint8_t NUM_DAYS = 10;
    const uint8_t NUM_HUMANS = 10;
}
class Human
{
public:
    explicit Human(uint8_t h)
        : m_id(h)
    {
        Q_ASSERT(0 <= h && h < constants::NUM_HUMANS);
    }
    operator uint8_t() const
    {
        return m_id;
    }
    private:
        uint8_t m_id;
};
class Day
{
public:
    explicit Day(uint8_t d)
        : m_id(d)
    {
        Q_ASSERT(0 <= d && d < constants::NUM_DAYS);
    }
    operator uint8_t() const
    {
        return m_id;
    }
private:
        uint8_t m_id;
};




namespace constants
{
    extern const std::vector<Human> HUMANS;
    extern const std::vector<Day> DAYS;
}
typedef QSet<Human> meeting_t;
typedef QList<meeting_t> meetings_t;
