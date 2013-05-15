#ifndef WALL_H
#define WALL_H

#include <QDialog>
#include <QVariantMap>

class QGraphicsScene;

class Prop;

namespace Ui {
class Wall;
}

class Wall : public QDialog
{
    Q_OBJECT
    
public:
    explicit Wall(const QString &name, const QString &image, QWidget *parent = 0);
    ~Wall();
    
    QString name() { return wallName; }
    void addProp(Prop *prop);
    void edit();
    QVariantMap map() const { return wallMap; }
    void setMap(const QVariantMap &m) { wallMap = m; }

signals:
    void updateWall(const QString &n, const QVariantMap &propMap);

private slots:
    void updateProps();

private:
    Ui::Wall *ui;
    QGraphicsScene *scene;
    QString wallName;
    QVariantMap wallMap;
};

#endif // WALL_H
