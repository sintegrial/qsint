#include "ledwidgetdemo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LedWidgetDemo w;
    w.show();
    
    return a.exec();
}
