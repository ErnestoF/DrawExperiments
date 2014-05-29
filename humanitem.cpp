#include "humanitem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

namespace
{
    const int rectWidth = 40;
    const int rectHeight = 40;
    const int headRad = 5;
    const int bodyLength = 15;
    const int xArmProjection = 10;
    const int yArmProjection = 10;
    const int legHeight = rectHeight - 2*headRad - bodyLength;
}
HumanItem::HumanItem(const QPointF &topLeft, QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , m_topLeft(topLeft)
    , m_state(NOT_REQUESTABLE)
{

}

int HumanItem::humanWidth()
{
    return rectWidth;
}

int HumanItem::humanHeight()
{
    return rectHeight;
}

QRectF HumanItem::boundingRect() const
{
    return QRectF(m_topLeft, QSize(humanWidth(), humanHeight()));
}

void HumanItem::paint(QPainter *painter, const QStyleOptionGraphicsItem * , QWidget *)
{
    QColor currentColor;
    if(ILL == m_state)
    {
        currentColor = Qt::red;
    }
    else if (NOT_ILL == m_state)
    {
        currentColor = Qt::green;
    }
    else if (REQUESTABLE == m_state)
    {
        currentColor == Qt::black;
    }
    else if (NOT_REQUESTABLE == m_state)
    {
        currentColor == Qt::gray;
    }
    else
    {
        Q_ASSERT(false);
    }
    painter->setBrush(QBrush(currentColor));
    painter->setPen(Qt::NoPen);
    const QPoint topMiddle(boundingRect().left() + boundingRect().width()/2, boundingRect().top());
    const QPoint headCenter(topMiddle + QPoint(0, headRad));

    painter->drawEllipse(headCenter, headRad,headRad);
    const QPoint headBottom = headCenter + QPoint(0, headRad);
    const QPoint bodyBottom = headBottom + QPoint(0, bodyLength);
    painter->setPen(QPen(currentColor, 2));
    painter->drawLine(headBottom, bodyBottom);
    painter->drawLine(headBottom, headBottom + QPoint(-xArmProjection, yArmProjection));
    painter->drawLine(headBottom, headBottom + QPoint(xArmProjection, yArmProjection));

    painter->drawLine(bodyBottom, bodyBottom + QPoint(-xArmProjection, legHeight));
    painter->drawLine(bodyBottom, bodyBottom + QPoint(xArmProjection, legHeight));
}

void HumanItem::setState(State const& state)
{
    m_state = state;
    update();
}
