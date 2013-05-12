#ifndef ROOMLIST_H
#define ROOMLIST_H

#include <QWidget>

class QPushButton;

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
    void addWalls(const QStringList &walls);

private:
    Ui::Room *ui;
    QPushButton *openButton;
};

#endif // ROOMLIST_H
