#ifndef LEDWIDGETDEMO_H
#define LEDWIDGETDEMO_H

#include <QWidget>

namespace Ui {
class LedWidgetDemo;
}

class LedWidgetDemo : public QWidget
{
    Q_OBJECT
    
public:
    explicit LedWidgetDemo(QWidget *parent = 0);
    ~LedWidgetDemo();
    
private:
    Ui::LedWidgetDemo *ui;
};

#endif // LEDWIDGETDEMO_H
