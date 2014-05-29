#ifndef GAME_H
#define GAME_H

#include <QList>
#include <QSet>
#include <QVector>

class Game
{
public:
    typedef size_t human_t;
    typedef size_t day_t;
    typedef QSet<human_t> meeting_t;
    typedef QList<meeting_t> meetings_t;
    typedef QVector<meetings_t> meetings_table_t;
    Game(const human_t numHumans, const day_t numDays);

    size_t numDays() const;
    size_t numHumans() const;
    bool isInfected(const day_t day, const human_t human) const;
    meetings_t meetings(const day_t day, const human_t human) const;
    meetings_t meetings(const day_t day) const;
    static Game generateGame(const size_t numHumans, const size_t numDays);

private:
    size_t m_numDays;
    size_t m_numHumans;
    QVector<QVector<bool> > m_contagionTable;
    meetings_table_t m_meetingsTable;
};

#endif // GAME_H
