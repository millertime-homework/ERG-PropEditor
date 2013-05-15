#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QPixmap>

#include "prop.h"
#include "wall.h"
#include "ui_wall.h"

Wall::Wall(const QString &name, const QString &image, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Wall),
    wallName(name)
{
    ui->setupUi(this);
    // note: the viewport size in-game is 1115x611 pixels. this is what we want to scale to.
    QGraphicsPixmapItem *backgroundImage = new QGraphicsPixmapItem(QPixmap(image).scaled(1115,611));
    scene = new QGraphicsScene();
    scene->addItem(backgroundImage);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setMaximumSize(1119,615);

    connect(this, SIGNAL(accepted()),
            this, SLOT(updateProps()));
}

Wall::~Wall()
{
    delete ui;
}

void Wall::addProp(Prop *prop)
{
    scene->addItem(prop);
}

void Wall::updateProps()
{
    foreach (QGraphicsItem *i, scene->items()) {
        Prop *p = dynamic_cast<Prop*>(i);
        if (p) {
            QRectF r = i->boundingRect();
            QPointF t = i->mapToScene(r.topLeft());
            QVariantMap propMap = wallMap.value(p->name()).toMap();
            propMap["left"]   = qRound(t.x());
            propMap["top"]    = qRound(t.y());
            propMap["width"]  = qRound(r.width());
            propMap["height"] = qRound(r.height());
            wallMap[p->name()] = propMap;
        }
    }
    emit updateWall(wallName, wallMap);
}
