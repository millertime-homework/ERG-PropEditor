#ifndef ROOMLIST_H
#define ROOMLIST_H

#include <QWidget>

namespace Ui {
class Room;
}

class Room : public QWidget
{
    Q_OBJECT
    
public:
    explicit Room(QWidget *parent = 0);
    ~Room();
    
    void displaySplash();

signals:
    void openRoom();

private:
    Ui::Room *ui;
};

#endif // ROOMLIST_H
