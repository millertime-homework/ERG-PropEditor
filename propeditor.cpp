#include "propeditor.h"
#include "ui_propeditor.h"

PropEditor::PropEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PropEditor)
{
    ui->setupUi(this);
    ui->frame_2->hide();
}

PropEditor::~PropEditor()
{
    delete ui;
}
