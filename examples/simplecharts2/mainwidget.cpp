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
                                         "2007" << "2008" << "2009" << "2010" << "2011" << "2012");
    itemModel->setVerticalHeaderLabels(QStringList() <<
                                       "Water" << "Coal" << "Oil" << "Sand" << "Stone" << "Wood" << "Concrete");
    itemModel->setHeaderData(0, Qt::Vertical, QColor(Qt::red), Qt::BackgroundRole);
    itemModel->setHeaderData(0, Qt::Vertical, QColor(Qt::white), Qt::ForegroundRole);
    itemModel->setHeaderData(1, Qt::Vertical, QColor(Qt::blue), Qt::BackgroundRole);
    itemModel->setHeaderData(1, Qt::Vertical, QColor(Qt::darkBlue), Qt::ForegroundRole);
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

    ui->Chart1->setBackground(QBrush(bg));
    ui->Chart1->setModel(itemModel);
    ui->Chart1->setBarType(QSint::BarChartPlotter::Stacked);
    ui->Chart1->setBarOpacity(0.95);
    ui->Chart1->setZeroLinePen(QPen(0xffa500));
    ui->Chart1->axisY()->setRanges(-50, 50);
    ui->Chart1->axisY()->setTicks(2, 10);
    ui->Chart1->axisY()->setTextColor(Qt::yellow);
    ui->Chart1->axisY()->setPen(QPen(Qt::gray));
    ui->Chart1->axisY()->setMinorTicksPen(QPen(Qt::blue));
    ui->Chart1->axisY()->setMinorGridPen(QPen(Qt::darkCyan, 1, Qt::DotLine));
    ui->Chart1->axisY()->setMajorTicksPen(QPen(Qt::magenta));
    ui->Chart1->axisY()->setMajorGridPen(QPen(Qt::darkGray));
    ui->Chart1->axisX()->setTextColor(Qt::green);
    ui->Chart1->axisX()->setPen(QPen(Qt::gray));
    ui->Chart1->axisX()->setMinorTicksPen(QPen(Qt::blue));
    ui->Chart1->axisX()->setMinorGridPen(QPen(Qt::darkBlue));
    ui->Chart1->axisX()->setMajorTicksPen(QPen(Qt::magenta));
    ui->Chart1->axisX()->setMajorGridPen(QPen(Qt::darkGray));
    ui->Chart1->setHighlightBrush(QBrush(QColor(0xffa500)));

    connect(ui->Chart1, SIGNAL(entered(const QModelIndex&)),
            this, SLOT(showTooltip1(const QModelIndex&)));

    ui->Chart2->setBackground(QBrush(bg));
    ui->Chart2->setModel(itemModel);
    ui->Chart2->setHighlightBrush(QBrush(QColor(0xffa500), Qt::Dense4Pattern));
    ui->Chart2->setHighlightAlpha(0.5);
    QFont pieFont("Arial", 12, QFont::Bold);
    ui->Chart2->setFont(pieFont);

    connect(ui->Chart1, SIGNAL(clicked(const QModelIndex&)),
            ui->Chart2, SLOT(setActiveIndex(const QModelIndex&)));

    ui->Chart3->setBackground(QBrush(bg));
    ui->Chart3->setModel(itemModel);
    ui->Chart3->setBarType(QSint::BarChartPlotter::Trend);
    ui->Chart3->setZeroLinePen(QPen(0xffa500));
    ui->Chart3->axisY()->setRanges(-20, 20);
    ui->Chart3->axisY()->setTextColor(Qt::yellow);
    ui->Chart3->axisY()->setPen(QPen(Qt::gray));
    ui->Chart3->axisY()->setMinorTicksPen(QPen(Qt::darkGray));
    ui->Chart3->axisY()->setMajorTicksPen(QPen(Qt::lightGray));
    ui->Chart3->axisX()->setTextColor(Qt::green);
    ui->Chart3->axisX()->setPen(QPen(Qt::gray));
    ui->Chart3->axisX()->setMinorTicksPen(QPen(Qt::darkGray));
    ui->Chart3->axisX()->setMajorTicksPen(QPen(Qt::lightGray));
    ui->Chart3->setHighlightBrush(QBrush(QColor(0xffa500)));

    ui->Chart4->setBackground(QBrush(bg));
    ui->Chart4->setModel(itemModel);
    ui->Chart4->setBarType(QSint::BarChartPlotter::Columns);
    ui->Chart4->setZeroLinePen(QPen(0xffa500));
    ui->Chart4->setBarScale(0.75);
    ui->Chart4->axisY()->setRanges(-20, 20);
    ui->Chart4->axisY()->setTextColor(Qt::yellow);
    ui->Chart4->axisY()->setPen(QPen(Qt::gray));
    ui->Chart4->axisY()->setMinorTicksPen(QPen(Qt::darkGray));
    ui->Chart4->axisY()->setMajorTicksPen(QPen(Qt::lightGray));
    ui->Chart4->axisY()->setMinorGridPen(QPen(Qt::darkCyan, 1, Qt::DotLine));
    ui->Chart4->axisX()->setTextColor(Qt::green);
    ui->Chart4->axisX()->setPen(QPen(Qt::gray));
    ui->Chart4->axisX()->setMinorTicksPen(QPen(Qt::darkGray));
    ui->Chart4->axisX()->setMajorTicksPen(QPen(Qt::lightGray));
    ui->Chart4->setHighlightBrush(QBrush(QColor(0xffa500)));

	ui->Chart5->setBackground(QBrush(bg));
    ui->Chart5->setModel(itemModel);
    ui->Chart5->setHighlightBrush(QBrush(QColor(0xffa500), Qt::Dense4Pattern));
    ui->Chart5->setHighlightAlpha(0.5);
    QFont ringFont("Arial", 10, QFont::Bold);
    ui->Chart5->setFont(ringFont);
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
                ui->Chart1->globalMousePos(),
                QString("Row %1   Col %2").arg(index.row()).arg(index.column())
                );
    }
    else
        QToolTip::hideText();
}

