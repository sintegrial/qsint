#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto newAction = new QAction(QIcon(":res/fileopen.png"), "Open File...");
    newAction->setToolTip("Open a document from the disk");
    ui->SplitButton->addAction(newAction);

    auto printAction = new QAction(QIcon(":res/fileprint.png"), "Print Document");
    printAction->setToolTip("Send current document to the printer");
    ui->SplitButton->addAction(printAction);

    auto saveAction = new QAction(QIcon(":res/filesave.png"), "Save File");
    saveAction->setToolTip("Store current document to the disk");
    ui->SplitButton->addAction(saveAction);

    ui->SplitButton->setDefaultAction(newAction);

    ui->SplitButton->setLastActionDefault(true);



    ui->SplitButton_2->addAction(newAction);
    ui->SplitButton_2->addAction(saveAction);
    ui->SplitButton_2->addAction(printAction);
    ui->SplitButton_2->setDefaultAction(newAction);


    ui->SplitButton_3->addAction(newAction);
    ui->SplitButton_3->addAction(saveAction);
    ui->SplitButton_3->addAction(printAction);
    ui->SplitButton_3->setDefaultAction(newAction);
    ui->SplitButton_3->setActionsToggle(true);
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

