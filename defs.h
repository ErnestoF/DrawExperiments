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

typedef size_t human_t;
typedef size_t day_t;
typedef QSet<human_t> meeting_t;
typedef QList<meeting_t> meetings_t;


