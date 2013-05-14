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
}

Wall::~Wall()
{
    delete ui;
}

void Wall::addProp(Prop *prop)
{
    scene->addItem(prop);
}

void Wall::showEvent(QShowEvent *)
{
    foreach (QGraphicsItem *i, scene->items()) {
        QGraphicsWidget *w = dynamic_cast<QGraphicsWidget*>(i);
        if (!w) continue;
        QString v = i->isVisible() ? "visible" : "hidden";
        qDebug() << w->objectName() << v;
    }
}
