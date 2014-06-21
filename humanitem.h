#ifndef HUMANITEM_H
#define HUMANITEM_H

#include "defs.h"

#include <QGraphicsItem>

class HumanItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit HumanItem(QPointF const& topLeft, QObject* p = 0, QGraphicsItem* parent = 0);
    static int humanWidth();
    static int humanHeight();
    virtual QRectF	boundingRect() const;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    void setState(State const& state);

Q_SIGNALS:
    void statusRequested();

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event)  override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event)  override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
private:
    QPointF m_topLeft;
    State m_state;
    bool m_isHovered;
};

#endif // HUMANITEM_H
