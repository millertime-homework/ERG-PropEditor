#ifndef ROOMLIST_H
#define ROOMLIST_H

#include <QWidget>
#include <QVariantMap>

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
    QVariantMap map() const { return roomMap; }
    void setMap(const QVariantMap &m) { roomMap = m; }
    QString toJson();

signals:
    void openRoom();

public slots:
    void setName(const QString &name);
    void addWall(Wall* wall);

private slots:
    void openWall(QListWidgetItem *item);
    void updateWallMap(const QString &n, const QVariantMap &propMap);

private:
    Ui::Room *ui;
    QPushButton *openButton;
    QList<Wall*> wallList;
    QVariantMap roomMap;

    Wall *findWall(const QString &name);
};

#endif // ROOMLIST_H
