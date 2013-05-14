#include <QDebug>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValueIterator>

#include "room.h"
#include "wall.h"
#include "prop.h"
#include "propeditor.h"
#include "ui_propeditor.h"

#define IMAGE_PATH "/Users/russellmiller/psu/capstone/src/fa2012cs487-teambanana/src/web/img/"

PropEditor::PropEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PropEditor)
{
    ui->setupUi(this);

    if (!ui->centralWidget->layout())
        ui->centralWidget->setLayout(new QVBoxLayout());

    tabs = new QTabWidget();
    ui->centralWidget->layout()->addWidget(tabs);

    Room *room = new Room();
    connect(room, SIGNAL(openRoom()),
            this, SLOT(openRoom()));
    tabs->addTab(room, "New Room");

    connect(ui->actionOpen, SIGNAL(triggered()),
            this, SLOT(openRoom()));
}

PropEditor::~PropEditor()
{
    delete ui;
}

void PropEditor::openRoom()
{
    QString path = QFileDialog::getOpenFileName(this, "Open a JSON Room File", "",
                                                "Room Files (*.js)");
    loadRoom(path);
}

void PropEditor::loadRoom(const QString &path)
{
    QFile f(path);
    if (!f.open(QFile::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Error opening file "+path);
        return;
    }

    QByteArray rawJson = f.readAll();
    QScriptValue sc;
    QScriptEngine engine;
    sc = engine.evaluate("room = {" + QString(rawJson) + "}");

    QVariantMap roomMap = sc.toVariant().toMap();
    QString roomName = roomMap.keys().at(0);
    Room *room = (Room*) tabs->currentWidget();
    room->setName(roomName);
    tabs->setTabText(tabs->currentIndex(), roomName);

    QVariantMap wallMap = roomMap.value(roomName).toMap().value("_walls").toMap();
    QStringList wallNames = wallMap.keys();
    foreach (QString wallName, wallNames) {
        QVariantMap wallProperties = wallMap.value(wallName).toMap();
        QString image = wallProperties.value("image").toString();
        Wall *wall = new Wall(wallName, IMAGE_PATH + image);

        QVariantMap propMap = wallProperties.value("_props").toMap();
        foreach (QString propId, propMap.keys()) {
            QVariantMap propProperties = propMap.value(propId).toMap();
            QString propName = propProperties.value("name").toString();
            QString propImage = propProperties.value("image").toString();
            Prop *prop = new Prop(propName, IMAGE_PATH + propImage);
            qreal propX = propProperties.value("left").toReal();
            qreal propY = propProperties.value("top").toReal();
            prop->setPos(propX, propY);
            qreal propW = propProperties.value("width").toReal();
            qreal propH = propProperties.value("height").toReal();
            prop->resize(propW, propH);
            wall->addProp(prop);
        }

        room->addWall(wall);
    }

    f.close();
}
