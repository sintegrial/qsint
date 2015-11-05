#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QMessageBox>

#include <QSintActions>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // create ActionGroups on ActionPanel

    QSint::ActionGroup *group1 = ui->ActionPanel->createGroup(QPixmap(":/res/filesave.png"), "Expandable Group");
    group1->addAction(ui->actionNew);
    group1->addAction(ui->actionLoad);
    group1->addWidget(new QPushButton("Just a button", this));
    group1->addAction(ui->actionSave);
    group1->addAction(ui->actionPrint);
    group1->addWidget(new QPushButton("Just another button", this));

    QSint::ActionGroup *group2 = ui->ActionPanel->createGroup(QPixmap(":/res/editredo.png"), "Non-Expandable Group", false);
    group2->addAction(ui->actionNew);
    group2->addAction(ui->actionLoad);
    group2->addAction(ui->actionSave);
    group2->addAction(ui->actionPrint);

    ui->ActionPanel->addWidget(new QLabel("Action Group without header", this));

    QSint::ActionGroup *group3 = ui->ActionPanel->createGroup();
    group3->addAction(ui->actionNew);

    QHBoxLayout *hbl = new QHBoxLayout();
    group3->groupLayout()->addLayout(hbl);
    hbl->addWidget(group3->addAction(ui->actionLoad, false));
    hbl->addWidget(group3->addAction(ui->actionSave, false));

    group3->addAction(ui->actionPrint);

    ui->ActionPanel->addStretch();


    // setup standalone ActionGroup

    ui->ActionGroup1->setScheme(QSint::WinXPPanelScheme::defaultScheme());

    ui->ActionGroup1->addWidget(ui->rbDefaultScheme);
    ui->ActionGroup1->addWidget(ui->rbXPBlueScheme);
    ui->ActionGroup1->addWidget(ui->rbXPBlue2Scheme);
    ui->ActionGroup1->addWidget(ui->rbVistaScheme);
    ui->ActionGroup1->addWidget(ui->rbMacScheme);
    ui->ActionGroup1->addWidget(ui->rbAndroidScheme);

    adjustSize();
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

void MainWindow::executeAction()
{
    QMessageBox::about(0, "Action clicked", "Do something here :)");
}

void MainWindow::on_rbDefaultScheme_toggled(bool b)
{
    if (b)
        ui->ActionPanel->setScheme(QSint::ActionPanelScheme::defaultScheme());
}

void MainWindow::on_rbXPBlueScheme_toggled(bool b)
{
    if (b)
        ui->ActionPanel->setScheme(QSint::WinXPPanelScheme::defaultScheme());

}

void MainWindow::on_rbXPBlue2Scheme_toggled(bool b)
{
    if (b)
        ui->ActionPanel->setScheme(QSint::WinXPPanelScheme2::defaultScheme());
}

void MainWindow::on_rbVistaScheme_toggled(bool b)
{
    if (b)
        ui->ActionPanel->setScheme(QSint::WinVistaPanelScheme::defaultScheme());
}

void MainWindow::on_rbMacScheme_toggled(bool b)
{
    if (b)
        ui->ActionPanel->setScheme(QSint::MacPanelScheme::defaultScheme());
}

void MainWindow::on_rbAndroidScheme_toggled(bool b)
{
    if (b)
        ui->ActionPanel->setScheme(QSint::AndroidPanelScheme::defaultScheme());
}

