#include <QDebug>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>

#include "prop.h"

Prop::Prop(const QString &name, const QString &image, QGraphicsItem *parent) :
    QGraphicsWidget(parent),
    propName(name),
    pixmap(QPixmap(image)),
    resizing(false)
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
    resizing = inCorner(event->scenePos());
    if (resizing)
        QApplication::setOverrideCursor(QCursor(Qt::SizeFDiagCursor));
    else
        QApplication::setOverrideCursor(QCursor(Qt::CrossCursor));
}

void Prop::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qreal deltaX = event->scenePos().x() - event->lastScenePos().x();
    qreal deltaY = event->scenePos().y() - event->lastScenePos().y();
    if (resizing)
        resize(boundingRect().width() + deltaX,
               boundingRect().height() + deltaY);
    else
        moveBy(deltaX, deltaY);
}

void Prop::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    resizing = false;
    QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
}

bool Prop::inCorner(const QPointF &scenePos)
{
    return ((scenePos.x() > x() + boundingRect().width() - 20) &&
            (scenePos.y() + boundingRect().height() - 20));
}
