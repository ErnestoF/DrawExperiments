#pragma once

#include "defs.h"
#include "abstractplayer.h"

#include <QGenericMatrix>
#include <QGraphicsScene>

#include <array>
#include <functional>

class HumanItem;
class QCheckBox;
class QGraphicsView;
class QGraphicsItemGroup;

class GuiPlayer : public AbstractPlayer
{
public:
    GuiPlayer(QString const& name,
              std::function<void()> restartCallback = 0);
    GuessResponse guess() const override;
    void tellGameResult(bool isWinner) override;
    void tellCurrentState(GameState const& gameState) override;
private: // methods
    void populateScene();
    void drawMeeting(Meeting const& meeting);
    void resetPlayer();
private: // attributes
    QGraphicsScene m_gameScene;
    QGraphicsView* m_view;
    mutable bool m_editMode;
    mutable Human m_guessedHuman;
    QCheckBox* m_doFinalGuessCheckBox;
    QGenericMatrix<std::tuple_size<decltype(constants::DAYS)>::value,
                   std::tuple_size<decltype(constants::HUMANS)>::value, HumanItem*> m_humanItemMatrix;
    meetings_t m_meetings;
    std::function<void()> m_restartCallback;
};
