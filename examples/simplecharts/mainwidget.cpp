#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QSintCharts>


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    ui->BarPlot->axisY()->setRanges(-80, 80);
    ui->BarPlot->axisY()->setTicks(2, 10);
    ui->BarPlot->axisY()->setPen(QPen(Qt::darkGray));
    ui->BarPlot->axisY()->setMinorTicksPen(QPen(Qt::gray));
    ui->BarPlot->axisY()->setMajorTicksPen(QPen(Qt::darkGray));
    //ui->BarPlot->axisY()->setMinorGridPen(QPen(Qt::gray));
    ui->BarPlot->axisY()->setMajorGridPen(QPen(Qt::lightGray));
    ui->BarPlot->axisY()->setTextColor(Qt::black);

    ui->BarPlot->axisX()->setPen(QPen(Qt::darkGray));
    ui->BarPlot->axisX()->setMinorTicksPen(QPen(Qt::gray));
    ui->BarPlot->axisX()->setMajorTicksPen(QPen(Qt::darkGray));
    ui->BarPlot->axisX()->setMajorGridPen(QPen(Qt::lightGray));
    ui->BarPlot->axisX()->setTextColor(Qt::black);

    ui->BarPlot->setBarSize(32, 128);
    ui->BarPlot->setBarOpacity(0.75);

    QLinearGradient bg(0,0,0,1);
    bg.setCoordinateMode(QGradient::ObjectBoundingMode);
    bg.setColorAt(1, Qt::white);
    bg.setColorAt(0.5, QColor(0xccccff));
    bg.setColorAt(0, Qt::white);
    ui->BarPlot->setBackground(QBrush(bg));

    itemModel = new QStandardItemModel(5,4,this);
    itemModel->setHorizontalHeaderLabels(QStringList() <<
                                         "2007" << "2008" << "2009" << "2010");
    itemModel->setVerticalHeaderLabels(QStringList() <<
                                       "Water" << "Coal" << "Oil" << "Sand" << "Stone");
    itemModel->setHeaderData(0, Qt::Vertical, QColor(Qt::red), Qt::BackgroundRole);
    itemModel->setHeaderData(0, Qt::Vertical, QColor(Qt::black), Qt::ForegroundRole);
    itemModel->setHeaderData(1, Qt::Vertical, QColor(Qt::blue), Qt::BackgroundRole);
    itemModel->setHeaderData(1, Qt::Vertical, QColor(Qt::darkBlue), Qt::ForegroundRole);
    itemModel->setHeaderData(2, Qt::Vertical, QColor(Qt::green), Qt::BackgroundRole);
    itemModel->setHeaderData(2, Qt::Vertical, QColor(Qt::darkGreen), Qt::ForegroundRole);
    itemModel->setHeaderData(3, Qt::Vertical, QColor(Qt::yellow), Qt::BackgroundRole);
    itemModel->setHeaderData(3, Qt::Vertical, QColor(Qt::darkRed), Qt::ForegroundRole);
    itemModel->setHeaderData(4, Qt::Vertical, QColor(Qt::white), Qt::BackgroundRole);

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 4; j++)
            itemModel->setData(itemModel->index(i,j), qrand()%60-30);

    ui->BarPlot->setModel(itemModel);

    // update single segment color - row 0 (Coal), col 1 (2008)
    itemModel->setData(itemModel->index(0,1), QColor(Qt::cyan), Qt::BackgroundRole);
    itemModel->setData(itemModel->index(0,1), QColor(Qt::red), Qt::ForegroundRole);


    ui->PieChart->setModel(itemModel);
    ui->PieChart->setBackground(QBrush(bg));


    ui->TableWidget->setModel(itemModel);
    connect(ui->TableWidget->selectionModel(), SIGNAL(currentColumnChanged(QModelIndex,QModelIndex)),
            this, SLOT(OnColumnChanged(QModelIndex,QModelIndex)));
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

void MainWidget::on_AddRowButton_clicked()
{
    QString name = ui->ChannelName->text();
    if (name.isEmpty())
        return;

    QColor color = ui->ChannelColorButton->color();

    int idx = ui->TableWidget->model()->rowCount();
    ui->TableWidget->model()->insertRow(idx);
    ui->TableWidget->model()->setHeaderData(idx, Qt::Vertical, name);
    ui->TableWidget->model()->setHeaderData(idx, Qt::Vertical, QBrush(color), Qt::BackgroundRole);
}

void MainWidget::on_AddColumnButton_clicked()
{
    QString name = ui->ColumnName->text();
    if (name.isEmpty())
        return;

    int idx = ui->TableWidget->model()->columnCount();
    ui->TableWidget->model()->insertColumn(idx);
    ui->TableWidget->model()->setHeaderData(idx, Qt::Horizontal, name);
}


void MainWidget::on_StackedButton_clicked()
{
    ui->BarPlot->setBarType(QSint::BarChartPlotter::Stacked);
    ui->BarPlot->repaint();
}

void MainWidget::on_NearButton_clicked()
{
    ui->BarPlot->setBarType(QSint::BarChartPlotter::Columns);
    ui->BarPlot->repaint();
}

void MainWidget::on_TrendButton_clicked()
{
    ui->BarPlot->setBarType(QSint::BarChartPlotter::Trend);
    ui->BarPlot->repaint();
}


void MainWidget::OnColumnChanged(QModelIndex current,QModelIndex)
{
    ui->PieChart->setActiveIndex(current.column());
}

