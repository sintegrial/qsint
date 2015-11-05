#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QModelIndex>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

protected:
    void changeEvent(QEvent *e);

protected Q_SLOTS:
    void showTooltip1(const QModelIndex& index);

private:
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
