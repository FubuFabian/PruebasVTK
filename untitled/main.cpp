#include <QtGui/QApplication>
#include "ChangeVolumePropertiesWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChangeVolumePropertiesWidget w;
    w.show();
    
    return a.exec();
}
