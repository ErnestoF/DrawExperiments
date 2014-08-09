#include "guiclient.h"

#include "gamestate.h"
#include "guessresponse.h"
#include "humanitem.h"
#include <QCoreApplication>
#include <QGraphicsScene>
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
    , m_gameScene(new QGraphicsScene())
    , m_view(new QGraphicsView(m_gameScene))
    , m_editMode(false)
    , m_guessedHuman(0)
    , m_humanItemMatrix(NUM_DAYS, std::vector<HumanItem*>(NUM_HUMANS, nullptr))
{
    m_view->showMaximized();
    populateScene();
}

GuiClient::~GuiClient()
{
    delete m_gameScene;
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
        m_gameScene->addText("CONGRATULATIONS, YOU ARE THE WINNER");
    }
    else
    {
        m_gameScene->addText("HAHAHA, LOOOSER");
    }
}

void GuiClient::tellCurrentState(const GameState &gameState)
{
    updateGameScene(gameState);
}

void GuiClient::populateScene()
{
    for(auto d : constants::DAYS)
        for(auto h : constants::HUMANS)
        {
            m_humanItemMatrix[d][h] = new HumanItem(QPoint(xLeft(h), yTop(d)));
            m_humanItemMatrix[d][h]->setState(NOT_REQUESTABLE);
            m_gameScene->addItem(m_humanItemMatrix[d][h]);
            QObject::connect(m_humanItemMatrix[d][h], &HumanItem::statusRequested,
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
   m_gameScene->addWidget(m_doFinalGuessCheckBox);
   m_doFinalGuessCheckBox->move(-150,m_gameScene->height()/2);

}

void GuiClient::updateGameScene(const GameState &gameState)
{
    for(auto d  : constants::DAYS)
    {
        for(auto h : constants::HUMANS)
        {
            m_humanItemMatrix[d][h]->setState(gameState.getHumanState(h,d));
        }
    }
    auto const& knownMeetings = gameState.getMeetings();
    for( auto& m : knownMeetings)
    {
        if(!contains(m_allKnownMeetings, m))
        {
            drawMeeting(m);
            m_allKnownMeetings.push_back(m);
        }
    }
}

void GuiClient::drawMeeting(const Meeting &meeting)
{
    bool up = m_allKnownMeetings.end() == std::find_if(m_allKnownMeetings.begin(),
                                                       m_allKnownMeetings.end(),
                                                      [&](const Meeting& oldMeeting)
    {
        return meeting.day() == oldMeeting.day();
    });
    auto diff_y1 = 4;
    auto diff_y2 = 14;
    auto day = meeting.day();
    auto yNear = up ? yTop(day) - diff_y1 : yBottom(day) + diff_y1;
    auto yAway = up ? yTop(day) - diff_y2 : yBottom(day) + diff_y2;
    QGraphicsItemGroup* meetingsItemGroup = new QGraphicsItemGroup;
    auto participants = meeting.humans();
    for(auto h : participants)
    {
        auto* meetingLine = new QGraphicsPolygonItem(QVector<QPointF>()
                                                     <<QPointF(xCenter(h), yNear)
                                                     <<QPointF(xCenter(h), yAway));
        meetingsItemGroup->addToGroup(meetingLine);
    }
    auto firstGuest = *std::min_element(participants.begin(), participants.end());
    auto lastGuest= *std::max_element(participants.begin(), participants.end());
    auto meetingLine = new QGraphicsPolygonItem(QVector<QPointF>()
                                                 <<QPointF(xCenter(firstGuest), yAway)
                                                 <<QPointF(xCenter(lastGuest) , yAway));
    meetingsItemGroup->addToGroup(meetingLine);
    m_gameScene->addItem(meetingsItemGroup);
}


