#include "ledwidgetdemo.h"
#include "ui_ledwidgetdemo.h"


LedWidgetDemo::LedWidgetDemo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LedWidgetDemo)
{
    ui->setupUi(this);

    ui->LED1->setColor(Qt::red);
    ui->LED3->setColor(Qt::green);
    ui->LED2->setColor(Qt::yellow);

    ui->LED4->setColors(Qt::black, Qt::darkGray);
}


LedWidgetDemo::~LedWidgetDemo()
{
    delete ui;
}
