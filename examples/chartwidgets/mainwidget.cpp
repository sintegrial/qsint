#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QSintCharts>


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    QLinearGradient bg(0,0,0,1);
    bg.setCoordinateMode(QGradient::ObjectBoundingMode);
    bg.setColorAt(1, Qt::white);
    bg.setColorAt(0.5, QColor(0xccccff));
    bg.setColorAt(0, Qt::white);

    ui->PieChart->setBackground(QBrush(bg));

	ui->PieChart->setCutoutPercentage(0.1);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWidget::on_AddButton_clicked()
{
    QString name = ui->ChannelName->text();
    QColor color = ui->ChannelColorButton->color();
    double value = ui->Value->value();

    ui->PieChart->addData(name, color, value);
}


void MainWidget::on_AddRandomButton_clicked()
{
	ui->PieChart->addData("", QColor(qrand()%256, qrand() % 256, qrand() % 256), qrand()%200-100);
}


void MainWidget::on_ResetButton_clicked()
{
	ui->PieChart->clear();
}
