#ifndef GUICLIENT_H
#define GUICLIENT_H

#include "abstractclient.h"

class QGraphicsScene;
class QGraphicsView;

class GuiClient : public AbstractClient
{
public:
    GuiClient(QString const& name);

    virtual ~GuiClient();
    std::set<human_t> guess(GameState const& gameState) const override;

private: // methods
    void populateScene();

private: // attributes
    QGraphicsScene* m_gameScene;
    QGraphicsView* m_gameView;
};

#endif // GUICLIENT_H
