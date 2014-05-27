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
    Game(const human_t numHumans, const day_t numDays);

    size_t numDays() const;
    size_t numHumans() const;
    bool isInfected(const day_t day, const human_t human) const;
    meetings_t meetings(const day_t day, const human_t human) const;
    meetings_t meetings(const day_t day) const;
    static Game generateGame(const human_t numHumans, const day_t numDays);

private:
    day_t m_numDays;
    human_t m_numHumans;
    QVector<QVector<bool> > m_contagionTable;
    QVector<meetings_t> m_meetingsTable;
};

#endif // GAME_H
