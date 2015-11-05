#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ColorPopup1 uses standard color dialog
    ui->ColorPopup1->setPickModeLeft(QSint::ColorButton::PM_COLORDIALOG);

    // ColorPopup2 uses ColorGrid color dialog (the default)
    ui->ColorPopup2->setColor(Qt::red);
    ui->ColorPopup2->setScheme(QSint::ColorGrid::baseColors());
    // Cell size can be modified as well.
    ui->ColorPopup2->setCellSize(24);

    ui->ColorPopup3->setColor(Qt::green);
    ui->ColorPopup3->setScheme(QSint::ColorGrid::namedColors());
    // Cell size can be modified as well.
    ui->ColorPopup3->setCellSize(16);

    ui->ColorPopup4->setColor(Qt::cyan);
    ui->ColorPopup4->setScheme(QSint::ColorGrid::defaultColors());

    ui->ColorPopup5->setColor(Qt::yellow);
    ui->ColorPopup5->setScheme(QSint::ColorGrid::defaultColors2());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
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

void MainWindow::on_ColorGrid1SchemeCombo_activated(int index)
{
    switch (index)
    {
    case 0:
        ui->ColorGrid1->setScheme(QSint::ColorGrid::defaultColors());
        break;

    case 1:
        ui->ColorGrid1->setScheme(QSint::ColorGrid::defaultColors2());
        break;

    case 2:
        ui->ColorGrid1->setScheme(QSint::ColorGrid::baseColors());
        break;

    case 3:
        ui->ColorGrid1->setScheme(QSint::ColorGrid::namedColors());
        break;
    }
}
