#ifndef HUMANITEM_H
#define HUMANITEM_H

#include <QGraphicsItem>
class HumanItem : public QGraphicsItem
{
public:
    enum State
    {
        NOT_REQUESTABLE,
        REQUESTABLE,
        ILL,
        NOT_ILL
    };
    explicit HumanItem(QPointF const& topLeft, QGraphicsItem* parent = 0);
    static int humanWidth();
    static int humanHeight();
    virtual QRectF	boundingRect() const;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    void setState(State const& state);
private:
    QPointF m_topLeft;
    State m_state;

};

#endif // HUMANITEM_H
