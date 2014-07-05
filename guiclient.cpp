#include "guiclient.h"

#include "gamestate.h"
#include "humanitem.h"
#include "randomclient.h" // todo remove
#include <QGraphicsScene>
#include <QTimer> // todo remove
namespace
{
    const uint16_t yOffset = 40;

    int yBottom(const int d, const u_int16_t nDays)
    {
      return  d == nDays - 1 ? HumanItem::humanHeight() : (HumanItem::humanHeight()+yOffset)*(nDays - d) - HumanItem::humanHeight();
    }
    int xLeft(const int h)
    {
        return h * HumanItem::humanWidth();
    }
    int yTop(const int d, const u_int16_t nDays)
    {

        return yBottom(d, nDays) - HumanItem::humanHeight();
    }
    int xCenter(const int h)
    {
        return xLeft(h) + HumanItem::humanWidth()/2;
    }

//    void drawMeeting(human_t human, day_t day, Game const* game, QGraphicsScene* scene)
//    {
//        auto meetings = game->meetings(day);
//        if(meetings.empty())
//        {
//            return;
//        }
//        auto firstMeetings = meetings.at(0);
//        auto secondMeetings = meetings.at(1);
//        auto diff_y1 = 4;
//        auto diff_y2 = 14;
//        auto nDays = game->numDays();
//        if(firstMeetings.contains(human))
//        {
//            for(auto h : firstMeetings)
//            {
//                auto* meetingLine = new QGraphicsPolygonItem(QVector<QPointF>()
//                                                             <<QPointF(xCenter(h), yTop(day, nDays)- diff_y1)
//                                                             <<QPointF(xCenter(h), yTop(day, nDays)- diff_y2));
//                scene->addItem(meetingLine);
//            }
//            auto firstGuest1 = *std::min_element(firstMeetings.begin(), firstMeetings.end());
//            auto lastGuest1= *std::max_element(firstMeetings.begin(), firstMeetings.end());
//            auto meetingLine1 = new QGraphicsPolygonItem(QVector<QPointF>()
//                                                        <<QPointF(xCenter(firstGuest1), yTop(day, nDays) - diff_y2)
//                                                        <<QPointF(xCenter(lastGuest1) , yTop(day, nDays)-  diff_y2));
//            scene->addItem(meetingLine1);

//        }
//        if(secondMeetings.contains(human))
//        {
//            for(auto h : secondMeetings)
//            {
//                auto* meetingLine = new QGraphicsPolygonItem(QVector<QPointF>()
//                                                             <<QPointF(xCenter(h), yBottom(day, nDays) + diff_y1)
//                                                             <<QPointF(xCenter(h), yBottom(day, nDays) + diff_y2));
//                scene->addItem(meetingLine);
//            }
//            auto firstGuest2 = *std::min_element(secondMeetings.begin(), secondMeetings.end());
//            auto lastGuest2= *std::max_element(secondMeetings.begin(), secondMeetings.end());
//            auto meetingLine2 = new QGraphicsPolygonItem(QVector<QPointF>()
//                                                        <<QPointF(xCenter(firstGuest2), yBottom(day, nDays) + diff_y2)
//                                                        <<QPointF(xCenter(lastGuest2), yBottom(day, nDays) + diff_y2));
//             scene->addItem(meetingLine2);
//        }

//    }

}

GuiClient::GuiClient(QString const& name)
    : AbstractClient(name)
    , m_gameScene(new QGraphicsScene())
{
    //populateScene();
}

GuiClient::~GuiClient()
{
    delete m_gameScene;
}

std::set<human_t> GuiClient::guess(const GameState & gameState) const
{
    drawGameState(gameState);
    RandomClient proxy("Proxy");
    return proxy.guess(gameState);
}

QGraphicsScene *GuiClient::getScene()
{
    return m_gameScene;
}

void GuiClient::populateScene()
{
    std::vector<std::vector<HumanItem*> > humansMatrix(constants::NUM_DAYS,std::vector<HumanItem*>(  constants::NUM_HUMANS,nullptr));
    for(size_t d = 0; d < constants::NUM_DAYS; ++d)
    {
        for(size_t h = 0; h < constants::NUM_HUMANS; ++h)
        {

            humansMatrix[d][h] = new HumanItem(QPoint(xLeft(h), yTop(d, constants::NUM_DAYS)));
            HumanItem* human = humansMatrix[d][h];
            if (constants::NUM_DAYS-1 == d)
            {
                human->setState(REQUESTABLE);
            }
            else
            {
                human->setState(NOT_REQUESTABLE);
            }
            m_gameScene->addItem(human);
//               scene->connect(human, &HumanItem::statusRequested, [d,h,human,&game,humansMatrix]()
//               {
//                  human->setState(game.isInfected(d,h) ? ILL : NOT_ILL);
//                  if (d >= 1)
//                  {
//                      Q_ASSERT(humansMatrix[d-1][h] );
//                      humansMatrix[d-1][h]->setState(REQUESTABLE);
//                  }

//               }); // todo make connection

            //scene->connect(human, &HumanItem::statusRequested, std::bind(&drawMeeting, h, d, &game, scene)); // todo make connections

        }
     }

}

void GuiClient::drawGameState(const GameState &gameState) const
{
    m_gameScene->clear();
    m_gameScene->disconnect();
    for(size_t d = 0; d < gameState.getNumDays(); ++d)
    {
        for(size_t h = 0; h < gameState.getNumHumans(); ++h)
        {
            HumanItem* human = new HumanItem(QPoint(xLeft(h), yTop(d, gameState.getNumDays())));
            human->setState(gameState.getHumanState(h,d));
            m_gameScene->addItem(human);
            // todo make connection
        }
    }
}
