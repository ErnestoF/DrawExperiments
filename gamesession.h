#pragma once

#include "abstractclient.h"
#include "server.h"
#include <QVector>

class GameSession
{
public:
  /**
   * @brief addPlayer Adds a new player for the game session.
   * @pre A player with the same name was not added before.
   */
  void addPlayer(AbstractClient * player);

  /**
   * @brief start Starts the game session
   * @pre The number of the added players is not zero.
   */
  void start();

private:
  QVector<AbstractClient *> m_players;
  Server m_server;
};
