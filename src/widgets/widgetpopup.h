#ifndef WIDGETPOPUP_H
#define WIDGETPOPUP_H

#include <QFrame>


namespace QSint
{


/**
    \brief Class showing a widget as popup window.
    \since 0.2

    setWidget() function allows you to specify the widget to be popped up.
    After widget is set, you normally should call show() slot in order to pop the
    widget up at the specified global position.

    WidgetPopup takes care about positioning of your widget on the screen so it will
    be always visible even if popped beside.
*/
class WidgetPopup : public QFrame
{
    Q_OBJECT

public:
    /** Constructor.

        If \a parent not specified (default), then popup widget gets
        attribute Qt::WA_DeleteOnClose and will be deleted after close.
      */
    WidgetPopup(QWidget *parent = 0);

    /** Sets widget to be popped up to \a widget.
        If \a own is true then the widget will be reparented to the popup widget.
      */
    void setWidget(QWidget *widget, bool own = true);
    /** Returns widget to be popped up.
      */
    inline QWidget* widget() const { return m_widget; }
    /** Returns true if widget is owned by this popup widget, false otherwise.
      */
    inline bool isOwned() const { return m_own; }

public Q_SLOTS:
    /** Pops up the widget at global coordinates \a coord.
      */
    void show(QPoint coord);

protected:
    QWidget *m_widget;
    bool m_own;
    QWidget *m_oldParent;
};


} // namespace

#endif // WIDGETPOPUP_H
