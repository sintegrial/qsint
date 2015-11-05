#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // setup ActionBox 1
    ui->ActionBox1->setIcon(QPixmap(":/res/fileopen.png"));
    ui->ActionBox1->header()->setText("Header of the group");
    connect(ui->ActionBox1->header(), SIGNAL(clicked()), this, SLOT(executeAction()));

    QSint::ActionLabel *a1 = ui->ActionBox1->createItem("This action has no icon");
    connect(a1, SIGNAL(clicked()), this, SLOT(executeAction()));
    QSint::ActionLabel *a2 = ui->ActionBox1->createItem(QPixmap(":/res/fileprint.png"),
                                                "This action has icon");
    connect(a2, SIGNAL(clicked()), this, SLOT(executeAction()));

    QLayout *hbl1 = ui->ActionBox1->createHBoxLayout();
    QSint::ActionLabel *a3 = ui->ActionBox1->createItem("1st action in row", hbl1);
    connect(a3, SIGNAL(clicked()), this, SLOT(executeAction()));
    QSint::ActionLabel *a4 = ui->ActionBox1->createItem("2nd action in row", hbl1);
    connect(a4, SIGNAL(clicked()), this, SLOT(executeAction()));

    // setup ActionBox 2
    ui->ActionBox2->setIcon(QPixmap(":/res/filesave.png"));
    ui->ActionBox2->header()->setText("Checkable actions allowed");
    connect(ui->ActionBox2->header(), SIGNAL(clicked()), this, SLOT(executeAction()));

    QSint::ActionLabel *b1 = ui->ActionBox2->createItem("Action 1 (Exclusive)");
    b1->setCheckable(true);
    b1->setAutoExclusive(true);
    b1->setChecked(true);
    QSint::ActionLabel *b2 = ui->ActionBox2->createItem("Action 2 (Exclusive)");
    b2->setCheckable(true);
    b2->setAutoExclusive(true);
    QSint::ActionLabel *b3 = ui->ActionBox2->createItem("Action 3 (Exclusive)");
    b3->setCheckable(true);
    b3->setAutoExclusive(true);

    QSint::ActionLabel *b4 = ui->ActionBox2->createItem("Non-exclusive but still checkable");
    b4->setCheckable(true);

    // setup ActionBox 3
    ui->ActionBox3->setIcon(QPixmap(":/res/fileprint.png"));
    ui->ActionBox3->header()->setText("Also, widgets allowed as well");

    ui->ActionBox3->addWidget(new QPushButton("PushButton", this));
    ui->ActionBox3->addWidget(new QCheckBox("CheckBox", this));
    QLayout *hbl3 = ui->ActionBox3->createHBoxLayout();
    ui->ActionBox3->addWidget(new QRadioButton("RadioButton 1", this), hbl3);
    ui->ActionBox3->addWidget(new QRadioButton("RadioButton 2", this), hbl3);

    // setup ActionBox 4
    ui->ActionBox4->setIcon(QPixmap(":/res/fileopen.png"));
    ui->ActionBox4->header()->setText("ActionBox with different scheme");

    ui->ActionBox4->createItem("This action has no icon");
    ui->ActionBox4->createItem(QPixmap(":/res/fileprint.png"),
                                                "This action has icon");
    QLayout *hbl4 = ui->ActionBox4->createHBoxLayout();
    ui->ActionBox4->createItem("1st action in row", hbl4);
    ui->ActionBox4->createItem("2nd action in row", hbl4);
    ui->ActionBox4->createItem("3rd action in row", hbl4);

    const char* ActionBoxNewStyle =
        "QSint--ActionBox {"
            "background-color: #333333;"
            "border: 1px solid #000000;"
            "text-align: left;"
        "}"

        "QSint--ActionBox:hover {"
            "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #666666, stop: 1 #333333);"
            "border: 1px solid #222222;"
        "}"

        "QSint--ActionBox QSint--ActionLabel[class='header'] {"
            "text-align: center;"
            "font: 14px bold;"
            "color: #999999;"
            "background-color: transparent;"
            "border: 1px solid transparent;"
        "}"

        "QSint--ActionBox QSint--ActionLabel[class='header']:hover {"
            "color: #aaaaaa;"
            "text-decoration: underline;"
            "border: 1px dotted #aaaaaa;"
        "}"

        "QSint--ActionBox QSint--ActionLabel[class='action'] {"
            "background-color: transparent;"
            "border: none;"
            "color: #777777;"
            "text-align: left;"
            "font: 11px;"
        "}"

        "QSint--ActionBox QSint--ActionLabel[class='action']:hover {"
            "color: #888888;"
            "text-decoration: underline;"
        "}"

        "QSint--ActionBox QSint--ActionLabel[class='action']:on {"
            "background-color: #ddeeff;"
            "color: #006600;"
        "}"
    ;

    ui->ActionBox4->setStyleSheet(ActionBoxNewStyle);
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
