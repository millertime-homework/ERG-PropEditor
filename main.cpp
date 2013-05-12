#include <QtGui/QApplication>
#include "propeditor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PropEditor w;
    w.show();
    
    return a.exec();
}
