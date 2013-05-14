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

private:
    QString propName;
    QPixmap pixmap;
    qreal width;
    qreal height;
};

#endif // PROP_H
