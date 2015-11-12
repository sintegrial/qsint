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

private Q_SLOTS:
    void on_PathPicker_beforePicked();
    void on_rbFile_toggled(bool);
    void on_rbFiles_toggled(bool);
    void on_rbDir_toggled(bool);
    void on_rbFileToSave_toggled(bool);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
