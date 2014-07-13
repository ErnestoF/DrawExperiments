#ifndef GUICLIENT_H
#define GUICLIENT_H

#include "defs.h"
#include "abstractclient.h"

class QGraphicsScene;
class QGraphicsView;

class GuiClient : public AbstractClient
{
public:
    GuiClient(QString const& name);

    virtual ~GuiClient();
    std::set<human_t> guess(GameState const& gameState) const override;
    void tellGameResult(bool isWinner) override;
    QGraphicsScene* getScene();
private: // methods
    void populateScene();
    void updateGameScene(GameState const& gameState) const;
    void requestStatus(human_t humanId) const;
    void drawMeeting(day_t day, const GameState &gameState) const;
private: // attributes
    mutable QGraphicsScene* m_gameScene;
    QGraphicsView* m_view;
    mutable bool m_editMode;
    mutable human_t m_guessedHuman;

};

#endif // GUICLIENT_H
