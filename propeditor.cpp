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

PropEditor::PropEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PropEditor)
{
    ui->setupUi(this);

    if (!ui->centralWidget->layout())
        ui->centralWidget->setLayout(new QVBoxLayout());

    tabs = new QTabWidget();
    ui->centralWidget->layout()->addWidget(tabs);

    newRoom();
    getImagePath();

    connect(ui->actionNew, SIGNAL(triggered()),
            this, SLOT(newRoom()));
    connect(ui->actionOpen, SIGNAL(triggered()),
            this, SLOT(openRoom()));
    connect(ui->actionSave, SIGNAL(triggered()),
            this, SLOT(saveRoom()));
    connect(ui->actionClose, SIGNAL(triggered()),
            this, SLOT(closeRoom()));
}

PropEditor::~PropEditor()
{
    delete ui;
}

void PropEditor::newRoom()
{
    Room *room = new Room();
    connect(room, SIGNAL(openRoom()),
            this, SLOT(openRoom()));
    int i = tabs->addTab(room, "New Room");
    tabs->setCurrentIndex(i);
}

void PropEditor::openRoom()
{
    QString path = QFileDialog::getOpenFileName(this, "Open a JSON Room File", "",
                                                "Room Files (*.js)");
    if (path.isEmpty())
        return;
    loadRoom(path);
    ui->actionSave->setEnabled(true);
    ui->actionClose->setEnabled(true);
}

void PropEditor::saveRoom()
{
    QString path = QFileDialog::getSaveFileName(this, "Save JSON Room", "",
                                                "Room Files (*.js)");
    if (path.isEmpty())
        return;
    QFile f(path);
    if (!f.open(QFile::WriteOnly)) {
        QMessageBox::critical(this, "Error", "Error saving file "+path);
        return;
    }

    Room *room = (Room*) tabs->currentWidget();
    QByteArray fileData = room->toJson().toAscii();
    f.write(fileData);
    f.close();
}

void PropEditor::closeRoom()
{
    tabs->removeTab(tabs->currentIndex());
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
    room->setMap(roomMap);
    room->setName(roomName);
    tabs->setTabText(tabs->currentIndex(), roomName);

    QVariantMap wallMap = roomMap.value(roomName).toMap().value("_walls").toMap();
    QStringList wallNames = wallMap.keys();
    foreach (QString wallName, wallNames) {
        QVariantMap wallProperties = wallMap.value(wallName).toMap();
        QString image = wallProperties.value("image").toString();
        QDir pathToImages(imagePath);
        QString pathToThisImage = pathToImages.filePath(image);
        Wall *wall = new Wall(wallName, pathToThisImage);

        QVariantMap propMap = wallProperties.value("_props").toMap();
        wall->setMap(propMap);
        foreach (QString propId, propMap.keys()) {
            QVariantMap propProperties = propMap.value(propId).toMap();
            QString propImage = propProperties.value("image").toString();
            QDir pathToImages(imagePath);
            QString pathToThisPropImage = pathToImages.filePath(propImage);
            Prop *prop = new Prop(propId, pathToThisPropImage);
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

void PropEditor::getImagePath()
{
    imagePath = QFileDialog::getExistingDirectory(this, "Open the image directory");
    if (imagePath.isEmpty())
        QMessageBox::critical(this, "Error", "Error: unable to read the image path. Assuming current directory");
}
