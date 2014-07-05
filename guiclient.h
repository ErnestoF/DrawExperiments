#ifndef GUICLIENT_H
#define GUICLIENT_H

#include "abstractclient.h"

class QGraphicsScene;

class GuiClient : public AbstractClient
{
public:
    GuiClient(QString const& name);

    virtual ~GuiClient();
    std::set<human_t> guess(GameState const& gameState) const override;
    QGraphicsScene* getScene();
private: // methods
    void populateScene();
    void drawGameState(GameState const& gameState) const;
private: // attributes
    mutable QGraphicsScene* m_gameScene;
};

#endif // GUICLIENT_H
