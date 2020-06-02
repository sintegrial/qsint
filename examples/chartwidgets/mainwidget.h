#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
    class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

protected slots:
    void on_AddButton_clicked();
    void on_AddRandomButton_clicked();
    void on_ResetButton_clicked();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWidget *ui;

    QStandardItemModel *itemModel;
};

#endif // MAINWIDGET_H
