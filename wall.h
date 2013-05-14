#ifndef WALL_H
#define WALL_H

#include <QDialog>

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

protected:
    void showEvent(QShowEvent *);

private:
    Ui::Wall *ui;
    QGraphicsScene *scene;
    QString wallName;
};

#endif // WALL_H
