#include <QDebug>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

#include "prop.h"

Prop::Prop(const QString &name, const QString &image, QGraphicsItem *parent) :
    QGraphicsWidget(parent),
    propName(name),
    pixmap(QPixmap(image))
{
    setObjectName(propName);
    setZValue(2);
}

void Prop::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    int w = boundingRect().width();
    int h = boundingRect().height();
    painter->drawPixmap(boundingRect().toRect(), pixmap.scaled(w, h));
}

void Prop::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void Prop::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qreal deltaX = event->scenePos().x() - event->lastScenePos().x();
    qreal deltaY = event->scenePos().y() - event->lastScenePos().y();
    setX(x() + deltaX);
    setY(y() + deltaY);
}
