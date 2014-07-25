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
{
    m_view->showMaximized();
}

GuiClient::~GuiClient()
{
    delete m_gameScene;
}

GuessResponse GuiClient::guess(bool finalGuessIsMade) const
{
    Q_UNUSED(finalGuessIsMade);
    m_editMode = true;
    while(m_editMode)
    {
        QCoreApplication::processEvents();
    }
    std::set<human_t> result;
    result.insert(m_guessedHuman);
    return GuessResponse::makeRegularGuess(result);
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
    m_gameScene->clear();
    for(size_t d = 0; d < gameState.getNumDays(); ++d)
    {
        for(size_t h = 0; h < gameState.getNumHumans(); ++h)
        {
            HumanItem* human = new HumanItem(QPoint(xLeft(h), yTop(d, gameState.getNumDays())));
            human->setState(gameState.getHumanState(h,d));
            m_gameScene->addItem(human);
            QObject::connect(human, &HumanItem::statusRequested,
                             [=]()
            {
                if(m_editMode)
                {
                    m_guessedHuman = h;
                    m_editMode = false;
                }
            });
        }
        if (0 < d)
        {
            drawMeeting(d, gameState);
        }
    }
    checkBox = new QCheckBox;
    m_gameScene->addWidget(checkBox);
    checkBox->move(-50,0);
}

void GuiClient::requestStatus(human_t humanId) const
{
    if (m_editMode)
    {
        m_guessedHuman = humanId;
        m_editMode = false;
    }
}

void GuiClient::drawMeeting(day_t day, const GameState &gameState) const
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
    const auto nDays = gameState.getNumDays();
    for(auto h : firstMeetings)
    {
        auto* meetingLine = new QGraphicsPolygonItem(QVector<QPointF>()
                                                     <<QPointF(xCenter(h), yTop(day, nDays)- diff_y1)
                                                     <<QPointF(xCenter(h), yTop(day, nDays)- diff_y2));
        m_gameScene->addItem(meetingLine);
    }
    auto firstGuest1 = *std::min_element(firstMeetings.begin(), firstMeetings.end());
    auto lastGuest1= *std::max_element(firstMeetings.begin(), firstMeetings.end());
    auto meetingLine1 = new QGraphicsPolygonItem(QVector<QPointF>()
                                                 <<QPointF(xCenter(firstGuest1), yTop(day, nDays) - diff_y2)
                                                 <<QPointF(xCenter(lastGuest1) , yTop(day, nDays)-  diff_y2));
    m_gameScene->addItem(meetingLine1);

    if(2 == meetings.size())
    {
        auto secondMeetings = meetings.at(1);
        for(auto h : secondMeetings)
        {
            auto* meetingLine = new QGraphicsPolygonItem(QVector<QPointF>()
                                                         <<QPointF(xCenter(h), yBottom(day, nDays) + diff_y1)
                                                         <<QPointF(xCenter(h), yBottom(day, nDays) + diff_y2));
            m_gameScene->addItem(meetingLine);
        }
        auto firstGuest2 = *std::min_element(secondMeetings.begin(), secondMeetings.end());
        auto lastGuest2= *std::max_element(secondMeetings.begin(), secondMeetings.end());
        auto meetingLine2 = new QGraphicsPolygonItem(QVector<QPointF>()
                                                    <<QPointF(xCenter(firstGuest2), yBottom(day, nDays) + diff_y2)
                                                    <<QPointF(xCenter(lastGuest2), yBottom(day, nDays) + diff_y2));
         m_gameScene->addItem(meetingLine2);
    }

}


