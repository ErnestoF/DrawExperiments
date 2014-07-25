#ifndef GUICLIENT_H
#define GUICLIENT_H

#include "defs.h"
#include "abstractclient.h"

class QCheckBox;
class QGraphicsScene;
class QGraphicsView;

class GuiClient : public AbstractClient
{
public:
    GuiClient(QString const& name);

    virtual ~GuiClient();
    GuessResponse guess(bool finalGuessIsMade) const override;
    void tellGameResult(bool isWinner) override;
    void tellCurrentState(GameState const& gameState) override;
    QGraphicsScene* getScene();
private: // methods
    void populateScene();
    void updateGameScene(GameState const& gameState);
    void requestStatus(human_t humanId) const;
    void drawMeeting(day_t day, const GameState &gameState) const;
private: // attributes
    QGraphicsScene* m_gameScene;
    QGraphicsView* m_view;
    mutable bool m_editMode;
    mutable human_t m_guessedHuman;
    QCheckBox* checkBox;

};

#endif // GUICLIENT_H
