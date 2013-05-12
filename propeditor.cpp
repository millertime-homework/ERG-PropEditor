#include <QDebug>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValueIterator>

#include "room.h"
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
    QStringList walls = wallMap.keys();
    room->addWalls(walls);

    f.close();
}
