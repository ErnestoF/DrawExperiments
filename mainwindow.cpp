#include "mainwindow.h"


#include "humanitem.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QGraphicsView>
#include <QHBoxLayout>

namespace
{


   QGraphicsScene* createSceneForGame(Game const& game, QObject* parent = 0)
   {
       QGraphicsScene* scene = new QGraphicsScene(parent);
       const int xDistance = 40;
       const int yDistance = 80;
       for(size_t d = 0; d < game.numDays(); ++d)
       {
           for(size_t h = 0; h < game.numHumans(); ++h)
           {
               HumanItem* human = new HumanItem(QPoint(xDistance*h, yDistance*d));
               human->setState(game.isInfected(d,h) ? HumanItem::ILL : HumanItem::NOT_ILL);
               scene->addItem(human);
           }
           if (0 < d && d < game.numDays()-1)
           {
               Game::meetings_t meetings = game.meetings(d);
               Q_ASSERT(2 == meetings.size());
               auto firstMeetings = meetings.at(0);
               auto secondMeetings = meetings.at(1);
               for(auto h : firstMeetings)
               {
                   auto* meetingLine = new QGraphicsPolygonItem(QVector<QPointF>()
                                                                <<QPointF(xDistance*h, yDistance*d-10)
                                                                <<QPointF(xDistance*h, yDistance*d-20));
                   scene->addItem(meetingLine);
               }
               auto firstGuest1 = *std::min_element(firstMeetings.begin(), firstMeetings.end());
               auto lastGuest1= *std::max_element(firstMeetings.begin(), firstMeetings.end());
               auto meetingLine1 = new QGraphicsPolygonItem(QVector<QPointF>()
                                                           <<QPointF(xDistance*firstGuest1, yDistance*d-20)
                                                           <<QPointF(xDistance*lastGuest1, yDistance*d-20));
               scene->addItem(meetingLine1);
               for(auto h : secondMeetings)
               {
                   auto* meetingLine = new QGraphicsPolygonItem(QVector<QPointF>()
                                                                <<QPointF(xDistance*h, yDistance*d+40)
                                                                <<QPointF(xDistance*h, yDistance*d+50));
                   scene->addItem(meetingLine);
               }
               auto firstGuest2 = *std::min_element(secondMeetings.begin(), secondMeetings.end());
               auto lastGuest2= *std::max_element(secondMeetings.begin(), secondMeetings.end());
               auto meetingLine2 = new QGraphicsPolygonItem(QVector<QPointF>()
                                                           <<QPointF(xDistance*firstGuest2, yDistance*d+50)
                                                           <<QPointF(xDistance*lastGuest2, yDistance*d+50));
                scene->addItem(meetingLine2);
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
