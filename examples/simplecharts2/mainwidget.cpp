#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QSintCharts>

#include <QStandardItemModel>
#include <QToolTip>


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    // data model
    QStandardItemModel* itemModel = new QStandardItemModel(7, 6, this);
    itemModel->setHorizontalHeaderLabels(QStringList() <<
                                         "2010" << "2011" << "2012" << "2013" << "2014" << "2015");
    itemModel->setVerticalHeaderLabels(QStringList() <<
                                       "Water" << "Coal" << "Oil" << "Sand" << "Stone" << "Wood" << "Concrete");
    itemModel->setHeaderData(0, Qt::Vertical, QColor(Qt::red), Qt::BackgroundRole);
    itemModel->setHeaderData(0, Qt::Vertical, QColor(Qt::white), Qt::ForegroundRole);
    itemModel->setHeaderData(1, Qt::Vertical, QColor(Qt::blue), Qt::BackgroundRole);
    itemModel->setHeaderData(1, Qt::Vertical, QColor(Qt::cyan), Qt::ForegroundRole);
    itemModel->setHeaderData(2, Qt::Vertical, QColor(Qt::green), Qt::BackgroundRole);
    itemModel->setHeaderData(2, Qt::Vertical, QColor(Qt::darkGreen), Qt::ForegroundRole);
    itemModel->setHeaderData(3, Qt::Vertical, QColor(Qt::yellow), Qt::BackgroundRole);
    itemModel->setHeaderData(3, Qt::Vertical, QColor(Qt::darkRed), Qt::ForegroundRole);
    itemModel->setHeaderData(4, Qt::Vertical, QColor(Qt::white), Qt::BackgroundRole);
    itemModel->setHeaderData(4, Qt::Vertical, QColor(Qt::darkMagenta), Qt::ForegroundRole);
    itemModel->setHeaderData(5, Qt::Vertical, QColor(Qt::magenta), Qt::BackgroundRole);
    itemModel->setHeaderData(5, Qt::Vertical, QColor(Qt::darkBlue), Qt::ForegroundRole);
    itemModel->setHeaderData(6, Qt::Vertical, QColor(Qt::cyan), Qt::BackgroundRole);
    itemModel->setHeaderData(6, Qt::Vertical, QColor(Qt::darkBlue), Qt::ForegroundRole);

    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 6; j++)
            itemModel->setData(itemModel->index(i,j),
                               j > 0 ? qrand()%20-10 : qrand()%15);


    // GUI
    ui->setupUi(this);

    QLinearGradient bg(0,0,0,1);
    bg.setCoordinateMode(QGradient::ObjectBoundingMode);
    bg.setColorAt(0, QColor(0x444444));
    //bg.setColorAt(0.2, Qt::black);
    bg.setColorAt(1, QColor(0x111111));

    /****************************************************
     *  Stacked Chart
     ****************************************************/
    ui->StackedChart->setModel(itemModel);
    ui->StackedChart->setTitle("Stacked Barchart");
    ui->StackedChart->setTitlePen(QPen(Qt::white));
    ui->StackedChart->setTitleFont(QFont("Arial", 12));
    ui->StackedChart->setBackground(QBrush(bg));
    ui->StackedChart->setBarType(QSint::BarChartPlotter::Stacked);
    ui->StackedChart->setBarOpacity(0.95);
    ui->StackedChart->setZeroLinePen(QPen(0xffa500));
    ui->StackedChart->axisY()->setRanges(-50, 50);
    ui->StackedChart->axisY()->setTicks(2, 10);
    ui->StackedChart->axisY()->setTextColor(Qt::yellow);
    ui->StackedChart->axisY()->setPen(QPen(Qt::gray));
    ui->StackedChart->axisY()->setMinorTicksPen(QPen(Qt::blue));
    ui->StackedChart->axisY()->setMinorGridPen(QPen(Qt::darkCyan, 1, Qt::DotLine));
    ui->StackedChart->axisY()->setMajorTicksPen(QPen(Qt::magenta));
    ui->StackedChart->axisY()->setMajorGridPen(QPen(Qt::darkGray));
    ui->StackedChart->axisX()->setTextColor(Qt::green);
    ui->StackedChart->axisX()->setPen(QPen(Qt::gray));
    ui->StackedChart->axisX()->setMinorTicksPen(QPen(Qt::blue));
    ui->StackedChart->axisX()->setMinorGridPen(QPen(Qt::darkBlue));
    ui->StackedChart->axisX()->setMajorTicksPen(QPen(Qt::magenta));
    ui->StackedChart->axisX()->setMajorGridPen(QPen(Qt::darkGray));
    ui->StackedChart->setHighlightBrush(QBrush(QColor(0xffa500)));

    connect(ui->StackedChart, SIGNAL(entered(const QModelIndex&)),
            this, SLOT(showTooltip1(const QModelIndex&)));

    /****************************************************
     *  Pie Chart
     ****************************************************/
    ui->PieChart->setTitle("Pie Chart");
    ui->PieChart->setTitlePen(QPen(Qt::green));
    ui->PieChart->setTitleFont(QFont("Arial", 12));
    ui->PieChart->setBackground(QBrush(bg));
    ui->PieChart->setModel(itemModel);
    ui->PieChart->setHighlightBrush(QBrush(QColor(0xffa500), Qt::Dense4Pattern));
    ui->PieChart->setHighlightAlpha(0.5);
    QFont pieFont("Arial", 12, QFont::Bold);
    ui->PieChart->setFont(pieFont);

    connect(ui->StackedChart, SIGNAL(clicked(const QModelIndex&)),
            ui->PieChart, SLOT(setActiveIndex(const QModelIndex&)));

    /****************************************************
     *  Trend Chart
     ****************************************************/
    ui->TrendChart->setBackground(QBrush(bg));
    ui->TrendChart->setModel(itemModel);
    ui->TrendChart->setTitle("Trend Chart");
    ui->TrendChart->setTitlePen(QPen(Qt::cyan));
    ui->TrendChart->setTitleFont(QFont("Arial", 12));
    ui->TrendChart->setBarType(QSint::BarChartPlotter::Trend);
    ui->TrendChart->setZeroLinePen(QPen(0xffa500));
    ui->TrendChart->axisY()->setRanges(-20, 20);
    ui->TrendChart->axisY()->setTextColor(Qt::yellow);
    ui->TrendChart->axisY()->setPen(QPen(Qt::gray));
    ui->TrendChart->axisY()->setMinorTicksPen(QPen(Qt::darkGray));
    ui->TrendChart->axisY()->setMajorTicksPen(QPen(Qt::lightGray));
    ui->TrendChart->axisX()->setTextColor(Qt::green);
    ui->TrendChart->axisX()->setPen(QPen(Qt::gray));
    ui->TrendChart->axisX()->setMinorTicksPen(QPen(Qt::darkGray));
    ui->TrendChart->axisX()->setMajorTicksPen(QPen(Qt::lightGray));
    ui->TrendChart->setHighlightBrush(QBrush(QColor(0xffa500)));

    /****************************************************
     *  Column Chart
     ****************************************************/
    ui->ColumnChart->setBackground(QBrush(bg));
    ui->ColumnChart->setModel(itemModel);
    ui->ColumnChart->setTitle("Column Barchart");
    ui->ColumnChart->setTitlePen(QPen(Qt::green));
    ui->ColumnChart->setTitleFont(QFont("Arial", 12));
    ui->ColumnChart->setBarType(QSint::BarChartPlotter::Columns);
    ui->ColumnChart->setZeroLinePen(QPen(0xffa500));
    ui->ColumnChart->setBarScale(0.75);
    ui->ColumnChart->axisY()->setRanges(-20, 20);
    ui->ColumnChart->axisY()->setTextColor(Qt::yellow);
    ui->ColumnChart->axisY()->setPen(QPen(Qt::gray));
    ui->ColumnChart->axisY()->setMinorTicksPen(QPen(Qt::darkGray));
    ui->ColumnChart->axisY()->setMajorTicksPen(QPen(Qt::lightGray));
    ui->ColumnChart->axisY()->setMinorGridPen(QPen(Qt::darkCyan, 1, Qt::DotLine));
    ui->ColumnChart->axisX()->setTextColor(Qt::green);
    ui->ColumnChart->axisX()->setPen(QPen(Qt::gray));
    ui->ColumnChart->axisX()->setMinorTicksPen(QPen(Qt::darkGray));
    ui->ColumnChart->axisX()->setMajorTicksPen(QPen(Qt::lightGray));
    ui->ColumnChart->setHighlightBrush(QBrush(QColor(0xffa500)));

    /****************************************************
     *  Ring Chart
     ****************************************************/
    ui->RingChart->setTitle("Ring Chart");
    ui->RingChart->setTitlePen(QPen(Qt::green));
    ui->RingChart->setTitleFont(QFont("Arial", 12));
    ui->RingChart->setBackground(QBrush(bg));
    ui->RingChart->setModel(itemModel);
    ui->RingChart->setHighlightBrush(QBrush(QColor(0xffa500), Qt::Dense4Pattern));
    ui->RingChart->setHighlightTextColor(Qt::blue);
    QFont ringFont("Arial", 10, QFont::Bold);
    ui->RingChart->setFont(ringFont);
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

void MainWidget::showTooltip1(const QModelIndex& index)
{
    if (index.isValid())
    {
        QToolTip::showText(
                ui->StackedChart->globalMousePos(),
                //QString("Row %1   Col %2").arg(index.row()).arg(index.column())
                QString("%1: %2")
                    .arg(index.model()->headerData(index.row(), Qt::Vertical).toString())
                    .arg(index.model()->data(index).toString())
                );
    }
    else
        QToolTip::hideText();
}

