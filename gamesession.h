#pragma once

#include "abstractclient.h"
#include "server.h"
#include <QList>

class GameSession
{
public:
  void addClient(AbstractClient const* client);

  /**
   * @brief start Starts the game session
   * @pre The number of the added clients is not zero.
   */
  void start();

private:
  QList<AbstractClient const*> m_clients;
  Server m_server;
};
