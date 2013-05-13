#ifndef ROOMLIST_H
#define ROOMLIST_H

#include <QWidget>

class QListWidgetItem;
class QPushButton;

class Wall;

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

public slots:
    void setName(const QString &name);
    void addWall(Wall* wall);

private slots:
    void openWall(QListWidgetItem *item);

private:
    Ui::Room *ui;
    QPushButton *openButton;
    QList<Wall*> wallList;

    Wall *findWall(const QString &name);
};

#endif // ROOMLIST_H
