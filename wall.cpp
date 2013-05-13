#include <QGraphicsPixmapItem>
#include <QPixmap>

#include "wall.h"
#include "ui_wall.h"

Wall::Wall(const QString &name, const QString &image, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Wall),
    wallName(name)
{
    ui->setupUi(this);
    // note: the viewport size in-game is 1115x611 pixels. this is what we want to scale to.
    QGraphicsPixmapItem *backgroundImage = new QGraphicsPixmapItem(QPixmap(image).copy(0,0,1115,611));
    QGraphicsScene *scene = new QGraphicsScene();
    scene->addItem(backgroundImage);
    ui->graphicsView->setScene(scene);
}

Wall::~Wall()
{
    delete ui;
}
