#pragma once

#include "defs.h"
#include "abstractplayer.h"
#include <QGenericMatrix>
#include <QGraphicsScene>

class HumanItem;
class QCheckBox;
class QGraphicsView;
class QGraphicsItemGroup;

class GuiPlayer : public AbstractPlayer
{
public:
    GuiPlayer(QString const& name);
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
