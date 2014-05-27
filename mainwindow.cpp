#include "mainwindow.h"


#include "humanitem.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QGraphicsView>
#include <QHBoxLayout>

namespace
{
    QGraphicsItemGroup* createHuman(const QColor penColor = Qt::black,
                                    const int xHeadCenter = 0,
                                    const int yHeadCenter = 0,
                                    QGraphicsItem * parent = 0)
    {
        const int headRadius = 4;
        const int penWidth = 2;
        const QPen pen(penColor, penWidth);
        QAbstractGraphicsShapeItem* head = new QGraphicsEllipseItem(xHeadCenter-headRadius,yHeadCenter-headRadius,2*headRadius,2*headRadius);
        head->setPen(pen);
        head->setBrush(penColor);
        const int bodyLength = 20;
        const QPointF neckPoint(xHeadCenter, yHeadCenter+headRadius);
        const QPointF bodyBottomPoint = neckPoint + QPointF(0.0, bodyLength);
        QAbstractGraphicsShapeItem* body = new QGraphicsPolygonItem(QVector<QPointF>()<< neckPoint << bodyBottomPoint);
        body->setPen(pen);
        const int armLength = 10;
        QAbstractGraphicsShapeItem* leftArm = new QGraphicsPolygonItem(QVector<QPointF>()<< neckPoint <<neckPoint + QPointF(-armLength, +armLength));
        QAbstractGraphicsShapeItem* rightArm = new QGraphicsPolygonItem(QVector<QPointF>()<< neckPoint <<neckPoint + QPointF(+armLength, +armLength));
        leftArm->setPen(pen);
        rightArm->setPen(pen);
        const int vLegLength = 15;
        const int hLegLength = 10;
        QAbstractGraphicsShapeItem* leftLeg = new QGraphicsPolygonItem(QVector<QPointF>()<< bodyBottomPoint <<bodyBottomPoint + QPointF(-hLegLength, +vLegLength));
        QAbstractGraphicsShapeItem* rightLeg = new QGraphicsPolygonItem(QVector<QPointF>()<< bodyBottomPoint <<bodyBottomPoint + QPointF(+hLegLength, +vLegLength));
        leftLeg->setPen(pen);
        rightLeg->setPen(pen);
        QGraphicsItemGroup* human = new QGraphicsItemGroup(parent);
        human->addToGroup(head);
        human->addToGroup(body);
        human->addToGroup(leftArm);
        human->addToGroup(rightArm);
        human->addToGroup(leftLeg);
        human->addToGroup(rightLeg);
        return human;
    }

   QGraphicsScene* createSceneForGame(Game const& game, QObject* parent = 0)
   {
       QGraphicsScene* scene = new QGraphicsScene(parent);
       const int xDistance = 40;
       const int yDistance = 80;
       for(size_t d = 0; d < game.numDays(); ++d)
       {
           for(size_t h = 0; h < game.numHumans(); ++h)
           {
               QGraphicsItemGroup* human = createHuman(game.isInfected(d,h) ? Qt::red : Qt::green, xDistance*h, yDistance*d);
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
    auto illHuman = new HumanItem(QPointF(-150,150));
    illHuman->setState(HumanItem::ILL);
    auto fitHuman = new HumanItem(QPointF(-100,150));
    m_scene->addItem(illHuman);
    m_scene->addItem(fitHuman);
    showMaximized();
    setCentralWidget(m_view);
}

MainWindow::~MainWindow()
{
}
