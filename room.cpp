#include <QPushButton>

#include "room.h"
#include "ui_room.h"

Room::Room(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Room)
{
    ui->setupUi(this);
    displaySplash();
}

Room::~Room()
{
    delete ui;
}

void Room::displaySplash()
{
    ui->normalFrame->hide();
    QPushButton *button = new QPushButton("Open...");
    connect(button, SIGNAL(clicked()),
            this, SIGNAL(openRoom()));
    ui->verticalLayout->addWidget(button);
}
