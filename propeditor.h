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
    
public slots:
    void openRoom();

private:
    Ui::PropEditor *ui;
    QTabWidget *tabs;

    void loadRoom(const QString &path);
};

#endif // PROPEDITOR_H
