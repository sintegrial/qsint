#include "widgetpopup.h"

#include <QVBoxLayout>
#include <QDesktopWidget>


namespace QSint
{


WidgetPopup::WidgetPopup(QWidget *parent) :
    QFrame(parent, Qt::Popup),
    m_widget(0),
    m_own(true),
    m_oldParent(0)
{
    setAttribute(Qt::WA_WindowPropagation);

    if (parentWidget() == NULL)
        setAttribute(Qt::WA_DeleteOnClose);

    setLayout(new QVBoxLayout());
    layout()->setContentsMargins(0,0,0,0);
}

void WidgetPopup::setWidget(QWidget *widget, bool own)
{
    if (m_widget)
    {
        layout()->removeWidget(m_widget);

        if (m_own)
        {
            m_widget->setParent(0);
            delete m_widget;
        }
        else
        {
            m_widget->setParent(m_oldParent);
        }
    }

    m_widget = widget;
    m_own = own;
    m_oldParent = 0;

    if (m_widget)
    {
        m_oldParent = m_widget->parentWidget();
        m_widget->setParent(this);
        layout()->addWidget(m_widget);
    }
}

void WidgetPopup::show(QPoint coord)
{
    // important to do this before following adjustments!
    QFrame::show();

    QRect screen(QDesktopWidget().availableGeometry());
    if (coord.x() < screen.x())
        coord.setX(screen.x());
    if (coord.y() < screen.y())
        coord.setY(screen.y());
    if (coord.x() > (screen.right()-width()))
        coord.setX(screen.right()-width());
    if (coord.y() > (screen.bottom()-height()))
        coord.setY(screen.bottom()-height());
    move(coord);
}


} // namespace

