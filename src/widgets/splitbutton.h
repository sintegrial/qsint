#ifndef CSPLITBUTTON_H
#define CSPLITBUTTON_H

#include <QWidget>
#include <QToolButton>
#include <QMenu>


namespace QSint
{


class SplitButton : public QWidget
{
    Q_OBJECT

public:
    explicit SplitButton(QWidget *parent = nullptr);

    void setDefaultAction(QAction *action);
    void setIconSize(int size);
    void setLastActionDefault(bool on);
    void setActionsToggle(bool on);

signals:

private slots:
    void onMenuShow();
    void onMenuTriggered(QAction *action);
    void onButtonClicked();

private:
    QToolButton *m_button;
    QToolButton *m_split;
    QMenu *m_menu;
    bool m_setLast = false;
    bool m_toggle = false;
};


}


#endif // CSPLITBUTTON_H
