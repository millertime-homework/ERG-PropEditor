#include <QPushButton>

#include "room.h"
#include "wall.h"
#include "ui_room.h"

Room::Room(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Room)
{
    ui->setupUi(this);
    ui->name->setText("New Room");
    displaySplash();

    connect(ui->walls, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(openWall(QListWidgetItem*)));
}

Room::~Room()
{
    delete ui;
}

void Room::displaySplash()
{
    ui->normalFrame->hide();
    openButton = new QPushButton("Open...");
    connect(openButton, SIGNAL(clicked()),
            this, SIGNAL(openRoom()));
    ui->verticalLayout->addWidget(openButton);
}

void Room::setName(const QString &name)
{
    ui->name->setText(name);
    openButton->hide();
    ui->normalFrame->show();
}

void Room::addWall(Wall* wall)
{
    wallList.append(wall);
    ui->walls->addItem(wall->name());
}

void Room::openWall(QListWidgetItem *item)
{
    Wall *w = findWall(item->text());
    if (w != NULL) {
        w->exec();
    }
}

Wall *Room::findWall(const QString &name)
{
    foreach (Wall *w, wallList) {
        if (w->name() == name) {
            return w;
        }
    }
    return NULL;
}
