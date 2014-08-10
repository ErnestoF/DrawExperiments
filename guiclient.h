#ifndef GUICLIENT_H
#define GUICLIENT_H

#include "defs.h"
#include "abstractclient.h"
#include <QGenericMatrix>
#include <QGraphicsScene>
#include <list>

class HumanItem;
class QCheckBox;
class QGraphicsView;
class QGraphicsItemGroup;

class GuiClient : public AbstractClient
{
public:
    GuiClient(QString const& name);
    GuessResponse guess() const override;
    void tellGameResult(bool isWinner) override;
    void tellCurrentState(GameState const& gameState) override;
private: // methods
    void populateScene();
    void drawMeeting(Meeting const& meeting);
private: // attributes
    QGraphicsScene m_gameScene;
    QGraphicsView* m_view;
    mutable bool m_editMode;
    mutable Human m_guessedHuman;
    QCheckBox* m_doFinalGuessCheckBox;
    QGenericMatrix<constants::NUM_DAYS, constants::NUM_HUMANS, HumanItem*> m_humanItemMatrix;
    meetings_t m_meetings;

};

#endif // GUICLIENT_H
