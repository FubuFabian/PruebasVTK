#include <QtGui/QApplication>
#include "VTKThreeViews.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VTKThreeViews w;
    w.show();
    
    return a.exec();
}
