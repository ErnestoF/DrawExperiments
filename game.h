#ifndef GAME_H
#define GAME_H

#include "defs.h"
#include <QVector>

class Game
{
public:
    Game();

    bool isInfected(const Day day, const Human human) const;
    meetings_t meetings(const Day day, const Human human) const;
    meetings_t meetings(const Day day) const;
    static Game generateGame();
    typedef QVector<meetings_t> meetings_table_t;

private:
    QVector<QVector<bool> > m_contagionTable;
    meetings_table_t m_meetingsTable;
};

#endif // GAME_H
