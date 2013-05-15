#ifndef PROP_H
#define PROP_H

#include <QGraphicsWidget>

class Prop : public QGraphicsWidget
{
public:
    Prop(const QString &name, const QString &image, QGraphicsItem *parent = 0);

    QString name() { return propName; }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

private:
    QString propName;
    QPixmap pixmap;
    bool resizing;

    bool inCorner(const QPointF &scenePos);
};

#endif // PROP_H
