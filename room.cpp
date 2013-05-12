#include <QPushButton>

#include "room.h"
#include "ui_room.h"

Room::Room(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Room)
{
    ui->setupUi(this);
    ui->name->setText("New Room");
    displaySplash();
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

void Room::addWalls(const QStringList &walls)
{
    ui->walls->addItems(walls);
}
