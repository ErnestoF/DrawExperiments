#ifndef ABSTRACTCLIENT_H
#define ABSTRACTCLIENT_H

#include "defs.h"
#include <set>
#include <QString>
class GameState;
class GuessResponse;
class AbstractClient
{
public:
   AbstractClient(QString const& name)
       : m_name(name)
   {}
   virtual GuessResponse guess() const = 0;

   QString getName() const
   {
       return m_name;
   }

   virtual void tellGameResult(bool ){};

   virtual void tellCurrentState(GameState const& gameState) = 0;
private:
   QString m_name;
};

#endif // ABSTRACTCLIENT_H
