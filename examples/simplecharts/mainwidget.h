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
    void on_AddRowButton_clicked();
    void on_AddColumnButton_clicked();

    void on_StackedButton_clicked();
    void on_NearButton_clicked();
    void on_TrendButton_clicked();

    void OnColumnChanged(QModelIndex,QModelIndex);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWidget *ui;

    QStandardItemModel *itemModel;
};

#endif // MAINWIDGET_H
