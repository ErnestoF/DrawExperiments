#include "guiclient.h"

#include "gamestate.h"
#include "guessresponse.h"
#include "humanitem.h"
#include <QCoreApplication>
#include <QGraphicsView>
#include <QDebug>
#include <QCheckBox>
using namespace constants;
namespace
{

    const uint16_t yOffset = 40;

    int yBottom(Day d)
    {
      return  d == NUM_DAYS - 1 ? HumanItem::humanHeight() : (HumanItem::humanHeight()+yOffset)*(NUM_DAYS - d) - HumanItem::humanHeight();
    }
    int xLeft(Human h)
    {
        return h * HumanItem::humanWidth();
    }
    int yTop(Day d)
    {

        return yBottom(d) - HumanItem::humanHeight();
    }
    int xCenter(Human h)
    {
        return xLeft(h) + HumanItem::humanWidth()/2;
    }

}

GuiClient::GuiClient(QString const& name)
    : AbstractClient(name)
    , m_view(new QGraphicsView(&m_gameScene))
    , m_editMode(false)
    , m_guessedHuman(0)
    , m_humanItemMatrix(std::vector<HumanItem*>(NUM_DAYS*NUM_HUMANS,nullptr).data())
{
    m_view->showMaximized();
    populateScene();
}

GuessResponse GuiClient::guess() const
{
    m_editMode = true;
    while(m_editMode)
    {
        QCoreApplication::processEvents();
    }
    if(m_doFinalGuessCheckBox->isChecked())
    {
        return GuessResponse::makeFinalGuess(m_guessedHuman);
    }
    else
    {
        return GuessResponse::makeRegularGuess({m_guessedHuman});
    }
}

void GuiClient::tellGameResult(bool isWinner)
{
    if(isWinner)
    {
        m_gameScene.addText("CONGRATULATIONS, YOU ARE THE WINNER");
    }
    else
    {
        m_gameScene.addText("HAHAHA, LOOOSER");
    }
}

void GuiClient::tellCurrentState(const GameState &gameState)
{
    for(auto d  : constants::DAYS)
    {
        for(auto h : constants::HUMANS)
        {
            m_humanItemMatrix(d,h)->setState(gameState.getHumanState(h,d));
        }
    }
    for( auto& m : gameState.getMeetings())
    {
        if(!contains(m_meetings, m))
        {
            drawMeeting(m);
            m_meetings.push_back(m);
        }
    }
}

void GuiClient::populateScene()
{
    for(auto d : constants::DAYS)
        for(auto h : constants::HUMANS)
        {
            m_humanItemMatrix(d,h) = new HumanItem(QPoint(xLeft(h), yTop(d)));
            m_humanItemMatrix(d,h)->setState(NOT_REQUESTABLE);
            m_gameScene.addItem(m_humanItemMatrix(d,h));
            QObject::connect(m_humanItemMatrix(d,h), &HumanItem::statusRequested,
                             [=]()
            {
                if(m_editMode)
                {
                    m_guessedHuman = h;
                    m_editMode = false;
                }
            });
        }
   m_doFinalGuessCheckBox = new QCheckBox("Make final guess");
   m_gameScene.addWidget(m_doFinalGuessCheckBox);
   m_doFinalGuessCheckBox->move(-150,m_gameScene.height()/2);

}

namespace
{
    const int Y_OFFSET_NEAR = 4;
    const int Y_OFFSET_AWAY = 14;
    QGraphicsItem* createVerticalMeetingsLine(int x, int y_from, int y_to)
    {
        return new QGraphicsPolygonItem(QVector<QPointF>({QPointF(x, y_from), QPointF(x, y_to)}));
    }
    QGraphicsItem* createHorizontalMeetingsLine(int x_from, int x_to, int y)
    {
        return new QGraphicsPolygonItem(QVector<QPointF>({QPointF(x_from, y), QPointF(x_to, y)}));
    }

}
void GuiClient::drawMeeting(const Meeting &meeting)
{
    bool drawAbove = contains_if(m_meetings, [&](const Meeting& oldMeeting){ return meeting.day() == oldMeeting.day(); });
    auto day = meeting.day();
    auto yNear = drawAbove ? yTop(day) - Y_OFFSET_NEAR : yBottom(day) + Y_OFFSET_NEAR;
    auto yAway = drawAbove ? yTop(day) - Y_OFFSET_AWAY : yBottom(day) + Y_OFFSET_AWAY;
    QGraphicsItemGroup* meetingsItemGroup = new QGraphicsItemGroup;
    auto participants = meeting.participants();
    for(auto p : participants)
    {
        meetingsItemGroup->addToGroup(createVerticalMeetingsLine(xCenter(p), yNear, yAway));
    }
    auto mostLeftParticipant = *std::min_element(participants.begin(), participants.end());
    auto mostRightParticipant = *std::max_element(participants.begin(), participants.end());
    meetingsItemGroup->addToGroup(createHorizontalMeetingsLine(xCenter(mostLeftParticipant), xCenter(mostRightParticipant), yAway));
    m_gameScene.addItem(meetingsItemGroup);
}


