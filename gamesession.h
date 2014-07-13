#pragma once

#include "abstractclient.h"
#include "server.h"
#include <QVector>

class GameSession
{
public:
  void addClient(AbstractClient * client);

  /**
   * @brief start Starts the game session
   * @pre The number of the added clients is not zero.
   */
  void start();

private:
  QVector<AbstractClient *> m_clients;
  Server m_server;
};
