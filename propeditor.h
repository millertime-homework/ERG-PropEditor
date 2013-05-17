#ifndef PROPEDITOR_H
#define PROPEDITOR_H

#include <QMainWindow>

class Wall;

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
    void newRoom();
    void openRoom();
    void saveRoom();
    void closeRoom();

private:
    Ui::PropEditor *ui;
    QTabWidget *tabs;

    void loadRoom(const QString &path);
};

#endif // PROPEDITOR_H
