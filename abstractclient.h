#ifndef ABSTRACTCLIENT_H
#define ABSTRACTCLIENT_H

#include "defs.h"
#include <set>
#include <QString>
class GameState;

class AbstractClient
{
public:
   AbstractClient(QString const& name)
       : m_name(name)
   {}
   virtual std::set<human_t> guess(GameState const& gameState) const = 0;

   QString getName() const
   {
       return m_name;
   }

   virtual void tellGameResult(bool ){};
private:
   QString m_name;
};

#endif // ABSTRACTCLIENT_H
