#include "mainwindow.h"


#include "humanitem.h"
#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QGraphicsView>
#include <QHBoxLayout>

#include <functional>
#include <memory>
#include <vector>

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

    void drawMeeting(Game::human_t human, Game::day_t day, Game const* game, QGraphicsScene* scene)
        {
            auto meetings = game->meetings(day);
            if(meetings.empty())
            {
                return;
            }
            auto firstMeetings = meetings.at(0);
            auto secondMeetings = meetings.at(1);
            auto diff_y1 = 4;
            auto diff_y2 = 14;
            auto nDays = game->numDays();
            if(firstMeetings.contains(human))
            {
                for(auto h : firstMeetings)
                {
                    auto* meetingLine = new QGraphicsPolygonItem(QVector<QPointF>()
                                                                 <<QPointF(xCenter(h), yTop(day, nDays)- diff_y1)
                                                                 <<QPointF(xCenter(h), yTop(day, nDays)- diff_y2));
                    scene->addItem(meetingLine);
                }
                auto firstGuest1 = *std::min_element(firstMeetings.begin(), firstMeetings.end());
                auto lastGuest1= *std::max_element(firstMeetings.begin(), firstMeetings.end());
                auto meetingLine1 = new QGraphicsPolygonItem(QVector<QPointF>()
                                                            <<QPointF(xCenter(firstGuest1), yTop(day, nDays) - diff_y2)
                                                            <<QPointF(xCenter(lastGuest1) , yTop(day, nDays)-  diff_y2));
                scene->addItem(meetingLine1);

            }
            if(secondMeetings.contains(human))
            {
                for(auto h : secondMeetings)
                {
                    auto* meetingLine = new QGraphicsPolygonItem(QVector<QPointF>()
                                                                 <<QPointF(xCenter(h), yBottom(day, nDays) + diff_y1)
                                                                 <<QPointF(xCenter(h), yBottom(day, nDays) + diff_y2));
                    scene->addItem(meetingLine);
                }
                auto firstGuest2 = *std::min_element(secondMeetings.begin(), secondMeetings.end());
                auto lastGuest2= *std::max_element(secondMeetings.begin(), secondMeetings.end());
                auto meetingLine2 = new QGraphicsPolygonItem(QVector<QPointF>()
                                                            <<QPointF(xCenter(firstGuest2), yBottom(day, nDays) + diff_y2)
                                                            <<QPointF(xCenter(lastGuest2), yBottom(day, nDays) + diff_y2));
                 scene->addItem(meetingLine2);
            }

        }
   QGraphicsScene* createSceneForGame(Game const& game, QObject* parent = 0)
   {
       QGraphicsScene* scene = new QGraphicsScene(parent);
       std::vector<std::vector<HumanItem*> > humansMatrix(game.numDays(),std::vector<HumanItem*>(  game.numHumans(),nullptr));
       for(size_t d = 0; d < game.numDays(); ++d)
       {
           for(size_t h = 0; h < game.numHumans(); ++h)
           {

               humansMatrix[d][h] = new HumanItem(QPoint(xLeft(h), yTop(d, game.numDays())));
               HumanItem* human = humansMatrix[d][h];
               if (game.numDays()-1 == d)
               {
                   human->setState(HumanItem::REQUESTABLE);
               }
               else
               {
                   human->setState(HumanItem::NOT_REQUESTABLE);
               }
               scene->addItem(human);
               scene->connect(human, &HumanItem::statusRequested, [d,h,human,&game,humansMatrix]()
               {
                  human->setState(game.isInfected(d,h) ? HumanItem::ILL : HumanItem::NOT_ILL);
                  if (d >= 1)
                  {
                      Q_ASSERT(humansMatrix[d-1][h] );
                      humansMatrix[d-1][h]->setState(HumanItem::REQUESTABLE);
                  }

               });

               scene->connect(human, &HumanItem::statusRequested,
                              std::bind(&drawMeeting, h, d, &game, scene));

           }
        }
       return scene;

   }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
  , m_game(Game::generateGame(10,10))
  , m_scene(createSceneForGame(m_game, this))
  , m_view(new QGraphicsView(m_scene, this))
{
    showMaximized();
    setCentralWidget(m_view);
}

MainWindow::~MainWindow()
{
}
