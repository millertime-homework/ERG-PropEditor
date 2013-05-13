#ifndef WALL_H
#define WALL_H

#include <QDialog>

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
    void edit();

private:
    Ui::Wall *ui;
    QString wallName;
};

#endif // WALL_H
