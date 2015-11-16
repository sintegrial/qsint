#include <QApplication>
#include "testwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestWidget w;
    w.show();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
    return a.exec();
}
