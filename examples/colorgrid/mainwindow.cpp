#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ColorPopup1 uses standard color dialog
    ui->ColorPopup1->setPickMode(QSint::ColorButton::PM_COLORDIALOG);

    // ColorPopup2 uses ColorGrid color dialog (the default)
    ui->ColorPopup2->setColor(Qt::red);
    ui->ColorPopup2->setColorScheme(QSint::BaseColors());
    // Cell size can be modified as well.
    ui->ColorPopup2->setCellSize(24);

    ui->ColorPopup3->setColor(Qt::green);
    ui->ColorPopup3->setColorScheme(QSint::SvgColors());
    // Cell size can be modified as well.
    ui->ColorPopup3->setCellSize(16);

    ui->ColorPopup4->setColor(Qt::cyan);
    ui->ColorPopup4->setColorScheme(QSint::OpenOfficeColors());

    ui->ColorPopup5->setColor(Qt::yellow);
    ui->ColorPopup5->setColorScheme(QSint::OpenOfficeColors());
    ui->ColorPopup5->setPickMode(QSint::ColorButton::PM_COLORGRID);


    // connect grid signals to the buttons and combos
    connect(ui->ColorGrid1, SIGNAL(picked(QColor)), ui->ColorPopup1, SLOT(setColor(QColor)));
    connect(ui->ColorGrid1, SIGNAL(picked(QColor)), ui->ColorCombo1, SLOT(setColor(QColor)));
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
        ui->ColorGrid1->setScheme(QSint::defaultColors());
        ui->ColorCombo1->setColors(*QSint::defaultColors());
        ui->ColorCombo2->setColors(*QSint::defaultColors());
        break;

    case 1:
        ui->ColorGrid1->setScheme(QSint::defaultColors2());
        ui->ColorCombo1->setColors(*QSint::defaultColors2());
        ui->ColorCombo2->setColors(*QSint::defaultColors2());
        break;

    case 2:
        ui->ColorGrid1->setScheme(QSint::baseColors());
        ui->ColorCombo1->setColors(*QSint::baseColors());
        ui->ColorCombo2->setColors(*QSint::baseColors());
        break;

    case 3:
        ui->ColorGrid1->setScheme(QSint::namedColors());
        ui->ColorCombo1->setColors(*QSint::namedColors());
        ui->ColorCombo2->setColors(*QSint::namedColors());
        break;
    }
}

void MainWindow::on_ColorCombo1_currentColorChanged(QColor color)
{
    ui->ColorLabel1->setText(color.name());
}

void MainWindow::on_ColorCombo2_currentColorChanged(QColor color)
{
    ui->ColorLabel2->setText(color.name());
}
