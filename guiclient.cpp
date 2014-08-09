#include "guiclient.h"

#include "gamestate.h"
#include "guessresponse.h"
#include "humanitem.h"
#include <QCoreApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QCheckBox>
namespace
{

    const uint16_t yOffset = 40;

    int yBottom(const int d, const uint16_t nDays)
    {
      return  d == nDays - 1 ? HumanItem::humanHeight() : (HumanItem::humanHeight()+yOffset)*(nDays - d) - HumanItem::humanHeight();
    }
    int xLeft(const int h)
    {
        return h * HumanItem::humanWidth();
    }
    int yTop(const int d, const uint16_t nDays)
    {

        return yBottom(d, nDays) - HumanItem::humanHeight();
    }
    int xCenter(const int h)
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
    , m_humanItemMatrix(constants::NUM_DAYS, std::vector<HumanItem*>(constants::NUM_HUMANS, nullptr))
{
    m_view->showMaximized();
    for(auto d : constants::DAYS)
        for(auto h : constants::HUMANS)
        {
            m_humanItemMatrix[d][h] = new HumanItem(QPoint(xLeft(h), yTop(d, constants::NUM_DAYS)));
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
    std::set<Human> result;
    result.insert(m_guessedHuman);
    return m_doFinalGuessCheckBox->isChecked() ? GuessResponse::makeFinalGuess(m_guessedHuman)
                                  :GuessResponse::makeRegularGuess(result);
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

QGraphicsScene *GuiClient::getScene()
{
    return m_gameScene;
}



void GuiClient::updateGameScene(const GameState &gameState)
{
    m_meetings.clear();
    for(auto d  : constants::DAYS)
    {
        for(auto h : constants::HUMANS)
        {
            m_humanItemMatrix[d][h]->setState(gameState.getHumanState(h,d));
        }
        drawMeeting(d, gameState);
    }
}

void GuiClient::requestStatus(Human humanId) const
{
    if (m_editMode)
    {
        m_guessedHuman = humanId;
        m_editMode = false;
    }
}

void GuiClient::drawMeeting(Day day, const GameState &gameState)
{
    auto meetings = gameState.getMeetings(day);
    if(meetings.empty())
    {
        return;
    }
    Q_ASSERT(0 < meetings.size() && meetings.size() <= 2 );


    auto firstMeetings = meetings.at(0);
    auto diff_y1 = 4;
    auto diff_y2 = 14;
    QGraphicsItemGroup* firstMeetingGroup = new QGraphicsItemGroup;
    for(auto h : firstMeetings)
    {
        auto* meetingLine = new QGraphicsPolygonItem(QVector<QPointF>()
                                                     <<QPointF(xCenter(h), yTop(day, constants::NUM_DAYS)- diff_y1)
                                                     <<QPointF(xCenter(h), yTop(day, constants::NUM_DAYS)- diff_y2));
        firstMeetingGroup->addToGroup(meetingLine);
    }
    auto firstGuest1 = *std::min_element(firstMeetings.begin(), firstMeetings.end());
    auto lastGuest1= *std::max_element(firstMeetings.begin(), firstMeetings.end());
    auto meetingLine1 = new QGraphicsPolygonItem(QVector<QPointF>()
                                                 <<QPointF(xCenter(firstGuest1), yTop(day, constants::NUM_DAYS) - diff_y2)
                                                 <<QPointF(xCenter(lastGuest1) , yTop(day, constants::NUM_DAYS)-  diff_y2));
    firstMeetingGroup->addToGroup(meetingLine1);
    m_gameScene->addItem(firstMeetingGroup);
    m_meetings.push_back(firstMeetingGroup);
    if(2 == meetings.size())
    {
        QGraphicsItemGroup* secondMeetingsGroup = new QGraphicsItemGroup;
        auto secondMeetings = meetings.at(1);
        for(auto h : secondMeetings)
        {
            auto* meetingLine = new QGraphicsPolygonItem(QVector<QPointF>()
                                                         <<QPointF(xCenter(h), yBottom(day, constants::NUM_DAYS) + diff_y1)
                                                         <<QPointF(xCenter(h), yBottom(day, constants::NUM_DAYS) + diff_y2));
            secondMeetingsGroup->addToGroup(meetingLine);
        }
        auto firstGuest2 = *std::min_element(secondMeetings.begin(), secondMeetings.end());
        auto lastGuest2= *std::max_element(secondMeetings.begin(), secondMeetings.end());
        auto meetingLine2 = new QGraphicsPolygonItem(QVector<QPointF>()
                                                    <<QPointF(xCenter(firstGuest2), yBottom(day, constants::NUM_DAYS) + diff_y2)
                                                    <<QPointF(xCenter(lastGuest2), yBottom(day, constants::NUM_DAYS) + diff_y2));
        secondMeetingsGroup->addToGroup(meetingLine2);
        m_gameScene->addItem(secondMeetingsGroup);
        m_meetings.push_back(secondMeetingsGroup);
    }

}


