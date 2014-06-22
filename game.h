#ifndef GAME_H
#define GAME_H

#include "defs.h"
#include <QVector>

class Game
{
public:
    Game(const human_t numHumans, const day_t numDays);

    size_t numDays() const;
    size_t numHumans() const;
    bool isInfected(const day_t day, const human_t human) const;
    meetings_t meetings(const day_t day, const human_t human) const;
    meetings_t meetings(const day_t day) const;
    static Game generateGame(const size_t numHumans, const size_t numDays);
    typedef QVector<meetings_t> meetings_table_t;

private:

    size_t m_numDays;
    size_t m_numHumans;
    QVector<QVector<bool> > m_contagionTable;
    meetings_table_t m_meetingsTable;
};

#endif // GAME_H
