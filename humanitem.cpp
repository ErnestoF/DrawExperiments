#include "humanitem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>


HumanItem::HumanItem(const QPointF &topLeft, QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , m_topLeft(topLeft)
    , m_state(NOT_REQUESTABLE)
{

}

QRectF HumanItem::boundingRect() const
{
    return QRectF(m_topLeft, QSize(40, 40));
}

void HumanItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    
    if(ILL == m_state)
    {
        QPixmap pixmap("ill.jpeg");
        painter->drawPixmap(option->rect, pixmap);
    }
    else
    {
        QPixmap pixmap("smiley.png");
        painter->drawPixmap(option->rect, pixmap);

    }
}

void HumanItem::setState(State const& state)
{
    m_state = state;
}
