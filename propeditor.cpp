#include <QVBoxLayout>
#include <QTabWidget>
#include <QFileDialog>

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

    QTabWidget *tw = new QTabWidget();
    ui->centralWidget->layout()->addWidget(tw);

    Room *room = new Room();
    connect(room, SIGNAL(openRoom()),
            this, SLOT(openRoom()));
    tw->addTab(room, "New Room");

    connect(ui->actionOpen, SIGNAL(triggered()),
            this, SLOT(openRoom()));
}

PropEditor::~PropEditor()
{
    delete ui;
}

void PropEditor::openRoom()
{
    QFileDialog fd;
    fd.setWindowTitle("Open a JSON Room File");
    fd.setFilter("Room Files (*.js)");
    fd.exec();
}
