#pragma once

#include "abstractplayer.h"
#include "moderator.h"
#include <QVector>

class GameSession
{
public:
  /**
   * @brief addPlayer Adds a new player for the game session.
   * @note The ownership of the pointer will not be shared.
   * @pre A player with the same name was not added before.
   */
  void addPlayer(AbstractPlayer * player);

  /**
   * @brief start Starts the game session
   * @pre The number of the added players is not zero.
   */
  void start();

private:
  QVector<AbstractPlayer *> m_players;
  Moderator m_server;
};
