#ifndef PROPEDITOR_H
#define PROPEDITOR_H

#include <QMainWindow>

namespace Ui {
class PropEditor;
}

class PropEditor : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PropEditor(QWidget *parent = 0);
    ~PropEditor();
    
private:
    Ui::PropEditor *ui;
};

#endif // PROPEDITOR_H