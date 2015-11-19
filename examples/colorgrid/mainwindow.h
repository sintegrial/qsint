#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_ColorGrid1SchemeCombo_activated(int);

    void on_ColorCombo1_currentColorChanged(QColor);
    void on_ColorCombo2_currentColorChanged(QColor);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
