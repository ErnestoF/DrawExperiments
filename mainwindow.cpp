#include "mainwindow.h"


#include "humanitem.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QGraphicsView>
#include <QHBoxLayout>


namespace
{
    const uint16_t yOffset = 40;

    int yBottom(const int d);
    int xLeft(const int h)
    {
        return h * HumanItem::humanWidth();
    }
    int yTop(const int d)
    {
        return d == 0 ? 0 : yBottom(d-1) +  yOffset;
    }
    int xCenter(const int h)
    {
        return xLeft(h) + HumanItem::humanWidth()/2;
    }
    int yBottom(const int d)
    {
        return yTop(d) + HumanItem::humanHeight();
    }

   QGraphicsScene* createSceneForGame(Game const& game, QObject* parent = 0)
   {
       QGraphicsScene* scene = new QGraphicsScene(parent);

       for(size_t d = 0; d < game.numDays(); ++d)
       {
           for(size_t h = 0; h < game.numHumans(); ++h)
           {
               HumanItem* human = new HumanItem(QPoint(xLeft(h), yTop(d)));
               human->setState(game.isInfected(d,h) ? HumanItem::ILL : HumanItem::NOT_ILL);
               scene->addItem(human);
           }
           if (0 < d && d < game.numDays()-1)
           {
               Game::meetings_t meetings = game.meetings(d);
               Q_ASSERT(2 == meetings.size());
               auto firstMeetings = meetings.at(0);
               auto secondMeetings = meetings.at(1);
               auto diff_y1 = 4;
               auto diff_y2 = 14;
               for(auto h : firstMeetings)
               {
                   auto* meetingLine = new QGraphicsPolygonItem(QVector<QPointF>()
                                                                <<QPointF(xCenter(h), yTop(d)- diff_y1)
                                                                <<QPointF(xCenter(h), yTop(d)- diff_y2));
                   scene->addItem(meetingLine);
               }
               auto firstGuest1 = *std::min_element(firstMeetings.begin(), firstMeetings.end());
               auto lastGuest1= *std::max_element(firstMeetings.begin(), firstMeetings.end());
               auto meetingLine1 = new QGraphicsPolygonItem(QVector<QPointF>()
                                                           <<QPointF(xCenter(firstGuest1), yTop(d) - diff_y2)
                                                           <<QPointF(xCenter(lastGuest1) , yTop(d)-  diff_y2));
               scene->addItem(meetingLine1);
               for(auto h : secondMeetings)
               {
                   auto* meetingLine = new QGraphicsPolygonItem(QVector<QPointF>()
                                                                <<QPointF(xCenter(h), yBottom(d) + diff_y1)
                                                                <<QPointF(xCenter(h), yBottom(d) + diff_y2));
                   scene->addItem(meetingLine);
               }
               auto firstGuest2 = *std::min_element(secondMeetings.begin(), secondMeetings.end());
               auto lastGuest2= *std::max_element(secondMeetings.begin(), secondMeetings.end());
               auto meetingLine2 = new QGraphicsPolygonItem(QVector<QPointF>()
                                                           <<QPointF(xCenter(firstGuest2), yBottom(d) + diff_y2)
                                                           <<QPointF(xCenter(lastGuest2), yBottom(d) + diff_y2));
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
