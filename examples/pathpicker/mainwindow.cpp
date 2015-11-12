#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //qApp->setStyle("fusion");
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

void MainWindow::on_PathPicker_beforePicked()
{
    int dialogFlags = QSint::PathPicker::DF_DEFAULT;

    if (ui->rbSystemDialog->isChecked())
        dialogFlags = QSint::PathPicker::DF_SYSTEM;

    ui->PathPicker->setDialogType(dialogFlags);
}

void MainWindow::on_rbFile_toggled(bool on)
{
    if (on)
        ui->PathPicker->setObjectsToPick(QSint::PathPicker::PF_EXISTING_FILE);
}

void MainWindow::on_rbFiles_toggled(bool on)
{
    if (on)
        ui->PathPicker->setObjectsToPick(QSint::PathPicker::PF_EXISTING_FILES);
}

void MainWindow::on_rbDir_toggled(bool on)
{
    if (on)
        ui->PathPicker->setObjectsToPick(QSint::PathPicker::PF_EXISTING_DIR);
}

void MainWindow::on_rbFileToSave_toggled(bool on)
{
    if (on)
        ui->PathPicker->setObjectsToPick(QSint::PathPicker::PF_SAVE_FILE);
}
