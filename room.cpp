#include <QDebug>
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
    connect(wall, SIGNAL(updateWall(QString,QVariantMap)),
            this, SLOT(updateWallMap(QString,QVariantMap)));
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

void Room::updateWallMap(const QString &n, const QVariantMap &propMap)
{
    QString roomName = ui->name->text();
    QVariantMap wallMap = roomMap.value(roomName).toMap();
    QVariantMap walls = wallMap.value("_walls").toMap();
    QVariantMap wallProperties = walls.value(n).toMap();
    wallProperties["_props"] = propMap;
    walls[n] = wallProperties;
    wallMap["_walls"] = walls;
    roomMap[roomName] = wallMap;
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

/*
    Can't find a JSON writer :(
*/
QString Room::toJson()
{
    QString ONE_TAB    = "    ";
    QString TWO_TABS   = ONE_TAB + ONE_TAB;
    QString THREE_TABS = ONE_TAB + TWO_TABS;
    QString FOUR_TABS  = ONE_TAB + THREE_TABS;
    QString FIVE_TABS  = ONE_TAB + FOUR_TABS;
    QString SIX_TABS   = ONE_TAB + FIVE_TABS;
    QString result = "'" + ui->name->text() + "': {\n";
    QVariantMap room = roomMap.value(ui->name->text()).toMap();
    result += ONE_TAB + "'id': '" + room.value("id").toString() + "',\n";
    result += ONE_TAB + "'x': " + room.value("x").toString() + ",\n";
    result += ONE_TAB + "'y': " + room.value("y").toString() + ",\n";
    if (room.contains("_triggers")) {
        QVariantList triggers = room.value("_triggers").toList();
        result += ONE_TAB + "'_triggers': [";
        foreach (QVariant t, triggers) {
            result += "'" + t.toString() + "'";
            if (t != triggers.last()) result += ",";
        }
        result += "],\n";
    }
    result += ONE_TAB + "'_walls': {\n";
    QVariantMap walls = room.value("_walls").toMap();
    QStringList wallKeys = walls.keys();
    foreach (QString wallKey, wallKeys) {
        result += TWO_TABS + "'" + wallKey + "': {\n";
        QVariantMap wall = walls.value(wallKey).toMap();
        result += THREE_TABS + "'name': '" + wall.value("name").toString() + "',\n";
        result += THREE_TABS + "'image': '" + wall.value("image").toString() + "'";
        if (wall.contains("destination")) {
            result += ",\n" + THREE_TABS + "'destination': {\n";
            QVariantMap destination = wall.value("destination").toMap();
            if (destination.contains("x")) {
                result += FOUR_TABS + "'x': " + destination.value("x").toString();
                if (destination.contains("y"))
                    result += ",\n";
                else
                    result += "\n";
            }
            if (destination.contains("y"))
                result += FOUR_TABS + "'y': " + destination.value("y").toString() + "\n";
            result += THREE_TABS + "}"; // end destination object
        }
        if (wall.contains("_triggers")) {
            result += ",\n" + THREE_TABS + "'_triggers': [";
            QVariantList triggers = room.value("_triggers").toList();
            foreach (QVariant t, triggers) {
                result += "'" + t.toString() + "'";
                if (t != triggers.last()) result += ",";
            }
            result += "]";
        }
        if (wall.contains("_props")) {
            result += ",\n" + THREE_TABS + "'_props': {\n";
            QVariantMap propMap = wall.value("_props").toMap();
            QStringList propKeys = propMap.keys();
            foreach (QString propKey, propKeys) {
                result += FOUR_TABS + "'" + propKey + "': {\n";
                QVariantMap prop = propMap.value(propKey).toMap();
                result += FIVE_TABS + "'name': '" + prop.value("name").toString() + "',\n";
                result += FIVE_TABS + "'image': '" + prop.value("image").toString() + "',\n";
                if (prop.contains("openImage"))
                    result += FIVE_TABS + "'openImage': '" + prop.value("openImage").toString() + "',\n";
                if (prop.contains("hoverImage"))
                    result += FIVE_TABS + "'hoverImage': '" + prop.value("hoverImage").toString() + "',\n";
                result += FIVE_TABS + "'width': " + prop.value("width").toString() + ",\n";
                result += FIVE_TABS + "'height': " + prop.value("height").toString() + ",\n";
                result += FIVE_TABS + "'top': " + prop.value("top").toString() + ",\n";
                result += FIVE_TABS + "'left': " + prop.value("left").toString();
                if (prop.contains("barrier"))
                    result += ",\n" + FIVE_TABS + "'barrier': '" + prop.value("barrier").toString() + "'";
                if (prop.contains("action"))
                    result += ",\n" + FIVE_TABS + "'action': '" + prop.value("action").toString() + "'";
                if (prop.contains("actionVariables")) {
                    result += ",\n" + FIVE_TABS + "'actionVariables': {\n";
                    QVariantMap actionVariables = prop.value("actionVariables").toMap();
                    if (actionVariables.contains("conversationName"))
                        result += SIX_TABS + "'conversationName': '" + actionVariables.value("conversationName").toString() + "'";
                    if (actionVariables.contains("isAnAction"))
                        result += ",\n" + SIX_TABS + "'isAnAction': '" + actionVariables.value("isAnAction").toString() + "'";
                    result += "\n" + FIVE_TABS + "}\n"; // end actionVariables object
                }
                result += FOUR_TABS + "}"; // end prop object
                if (propKey != propKeys.last())
                    result += ",";
                result += "\n";
            }
            result += THREE_TABS + "}\n"; // end '_props' object
        }
        if (!result.endsWith("\n")) result += "\n";
        result += TWO_TABS + "}"; // end wall object
        if (wallKey != wallKeys.last())
            result += ",";
        result += "\n";
    }
    result += ONE_TAB + "}\n"; // end '_walls' object
    result += "}"; // end room object
    return result;
}
