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

protected slots:
    void executeAction();

    void on_rbDefaultScheme_toggled(bool);
    void on_rbXPBlueScheme_toggled(bool);
    void on_rbXPBlue2Scheme_toggled(bool);
    void on_rbVistaScheme_toggled(bool);
    void on_rbMacScheme_toggled(bool);
    void on_rbAndroidScheme_toggled(bool);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
