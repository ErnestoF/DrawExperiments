#ifndef GAME_H
#define GAME_H

#include "defs.h"
#include <QVector>

class Game
{
public:
    Game();

    bool isInfected(const Day day, const Human human) const;
    meetings_t meetings() const;
    static Game generateGame();
private:
    QVector<QVector<bool> > m_contagionTable;
    meetings_t m_meetings;
};

#endif // GAME_H
