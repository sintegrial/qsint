#include "testwidget.h"
#include "ui_testwidget.h"

TestWidget::TestWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestWidget)
{
    qApp->setStyle("fusion");

    ui->setupUi(this);

//    QPalette palette1;
//    QPixmap bkgnd("e:/tmp/t.png");
//    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);

//    palette1.setBrush(QPalette::Background, bkgnd);
//    this->setPalette(palette1);

    // donut (default style)
    ui->RoundBar1->setFormat("%v");
    ui->RoundBar1->setDecimals(0);
    connectToSlider(ui->RoundBar1);

    // pie
    ui->RoundBar2->setNullPosition(QSint::RoundProgressBar::PositionRight);
    ui->RoundBar2->setBarStyle(QSint::RoundProgressBar::StylePie);
    connectToSlider(ui->RoundBar2);

    // line
    ui->RoundBar3->setFormat("%m");
    ui->RoundBar3->setBarStyle(QSint::RoundProgressBar::StyleLine);
    connectToSlider(ui->RoundBar3);

    // expand
    ui->ExpandBar1->setBarStyle(QSint::RoundProgressBar::StyleExpand);
    connectToSlider(ui->ExpandBar1);

    // donut (customized via QPalette + gradient)
    QPalette p1(palette());
    p1.setBrush(QPalette::Background, Qt::NoBrush);
    p1.setBrush(QPalette::AlternateBase, Qt::black);
    p1.setColor(QPalette::Text, Qt::yellow);
    ui->RoundBar4->setPalette(p1);

    ui->RoundBar4->setNullPosition(QSint::RoundProgressBar::PositionLeft);
    ui->RoundBar4->setDecimals(0);

    // make a gradient from green over yellow to red
    QGradientStops gradientPoints;
    gradientPoints << QGradientStop(0, Qt::green) << QGradientStop(0.5, Qt::yellow) << QGradientStop(1, Qt::red);
    // and set it
    ui->RoundBar4->setDataColors(gradientPoints);

    connectToSlider(ui->RoundBar4);

    // pie (customized via QPalette + gradient)
    QPalette p2(p1);
    p2.setBrush(QPalette::Base, Qt::white);
    p2.setColor(QPalette::Text, Qt::darkMagenta);
    p2.setColor(QPalette::Shadow, Qt::green);
    ui->RoundBar5->setPalette(p2);
    ui->RoundBar5->setNullPosition(QSint::RoundProgressBar::PositionRight);
    ui->RoundBar5->setBarStyle(QSint::RoundProgressBar::StylePie);
    ui->RoundBar5->setDataColors(gradientPoints);   // here gradient colors are set
    connectToSlider(ui->RoundBar5);

    // line style with custom outline
    ui->RoundBar6->setDecimals(2);
    ui->RoundBar6->setBarStyle(QSint::RoundProgressBar::StyleLine);
    ui->RoundBar6->setOutlinePenWidth(18);
    ui->RoundBar6->setDataPenWidth(10);
    connectToSlider(ui->RoundBar6);

    // expand with gradient
    ui->ExpandBar2->setBarStyle(QSint::RoundProgressBar::StyleExpand);
    ui->ExpandBar2->setDecimals(0);
    ui->ExpandBar2->setPalette(p2);
    ui->ExpandBar2->setDataColors(gradientPoints);   // here gradient colors are set
    connectToSlider(ui->ExpandBar2);

    // big one
    connectToSlider(ui->RoundBar7);
}

TestWidget::~TestWidget()
{
    delete ui;
}

void TestWidget::connectToSlider(QSint::RoundProgressBar *bar)
{
    bar->setRange(ui->Slider->minimum(), ui->Slider->maximum());
    bar->setValue(ui->Slider->value());
    connect(ui->Slider, SIGNAL(valueChanged(int)), bar, SLOT(setValue(int)));
}
