#include "plotterbase.h"
#include "axisbase.h"


namespace QSint
{


PlotterBase::PlotterBase(QWidget *parent) :
    QWidget(parent),
    m_model(0),
    m_repaint(true),
    m_antiAliasing(false),
    m_highlight(false)
{
    m_axisX = m_axisY = 0;

    setBorderPen(QPen(Qt::gray));
    setBackground(QBrush(Qt::lightGray));
    setItemPen(QPen(Qt::darkGray));

    setHighlightAlpha(0.5);
    setHighlightTextColor(Qt::white);
    setHighlightPen(QPen(Qt::black));
    setHighlightBrush(QBrush(Qt::gray));

    setModel(0);

    setMouseTracking(true);
}


void PlotterBase::setTitle(const QString &title)
{
    m_title = title;

    update();
}


void PlotterBase::setTitlePen(const QPen &titlePen)
{
    m_titlePen = titlePen;

    update();
}


void PlotterBase::setTitleFont(const QFont &titleFont)
{
    m_titleFont = titleFont;

    update();
}


void PlotterBase::setBorderPen(const QPen &pen)
{
    m_pen = pen;

    update();
}


void PlotterBase::setBackground(const QBrush &brush)
{
    m_bg = brush;

    update();
}


void PlotterBase::setItemPen(const QPen &pen)
{
    m_itemPen = pen;

    update();
}


void PlotterBase::setFont(const QFont &font)
{
    m_font = font;

    update();
}


void PlotterBase::setHighlightTextColor(const QColor &color)
{
    m_hlTextColor = color;

    update();
}


void PlotterBase::setHighlightPen(const QPen &pen)
{
    m_hlPen = pen;

    update();
}


void PlotterBase::setHighlightBrush(const QBrush &brush)
{
    m_hlBrush = brush;

    update();
}


void PlotterBase::setHighlightAlpha(double alpha)
{
    m_hlAlpha = alpha;

    update();
}


void PlotterBase::setTextFormat(const QString &textFormat)
{
    m_textFormat = textFormat;

    update();
}


QRect PlotterBase::dataRect() const
{
    QRect p_rect(rect());

    if (m_axisX)
        p_rect.setBottom(p_rect.bottom() - m_axisX->offset());

    if (m_axisY)
        p_rect.setLeft(p_rect.left() + m_axisY->offset());

    if (!m_title.isEmpty())
    {
        QRect textRect = QFontMetrics(m_titleFont).boundingRect(m_title);
        p_rect.setTop(textRect.height() + 8);   // 4px extra margin
    }

    return p_rect;
}


void PlotterBase::setModel(QAbstractItemModel *model)
{
    if (m_model)
        m_model->disconnect(this);

    m_model = model;

    if (m_axisX)
        m_axisX->setModel(model);

    if (m_axisY)
        m_axisY->setModel(model);

    if (m_model)
    {
        connect(m_model, SIGNAL(dataChanged(const QModelIndex &,const QModelIndex &)),
                this, SLOT(scheduleUpdate()));

        connect(m_model, SIGNAL(headerDataChanged(Qt::Orientation, int, int)),
                this, SLOT(scheduleUpdate()));

        connect(m_model, SIGNAL(columnsInserted(const QModelIndex &, int, int)),
                this, SLOT(scheduleUpdate()));

        connect(m_model, SIGNAL(columnsRemoved(const QModelIndex &, int, int)),
                this, SLOT(scheduleUpdate()));

        connect(m_model, SIGNAL(rowsInserted(const QModelIndex &, int, int)),
                this, SLOT(scheduleUpdate()));

        connect(m_model, SIGNAL(rowsRemoved(const QModelIndex &, int, int)),
                this, SLOT(scheduleUpdate()));
    }
}


void PlotterBase::scheduleUpdate()
{
    m_repaint = true;

    update();
}


void PlotterBase::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit pressed(m_indexUnderMouse);

        m_indexClick = m_indexUnderMouse;

        //qDebug() << "pressed: " << m_indexUnderMouse;
    }
}


void PlotterBase::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit doubleClicked(m_indexUnderMouse);

        //qDebug() << "doubleClicked: " << m_indexUnderMouse;
    }
}


void PlotterBase::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_indexClick == m_indexUnderMouse && event->button() == Qt::LeftButton)
    {
        emit clicked(m_indexUnderMouse);

        m_indexClick = QModelIndex();

        //qDebug() << "clicked: " << m_indexUnderMouse;
    }
}


void PlotterBase::mouseMoveEvent(QMouseEvent *event)
{
    m_mousePos = event->pos();

    update();
}


void PlotterBase::leaveEvent(QMouseEvent *event)
{
    m_mousePos = QPoint();
    m_indexUnderMouse = m_indexClick = QModelIndex();

    repaint();

    QWidget::leaveEvent(event);
}


void PlotterBase::resizeEvent(QResizeEvent *event)
{
    m_mousePos = QPoint();
    m_indexUnderMouse = m_indexClick = QModelIndex();

    QWidget::resizeEvent(event);
}


void PlotterBase::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    if (m_antiAliasing)
        p.setRenderHint(QPainter::Antialiasing);

    drawBackground(p);

    drawTitle(p);

    drawAxes(p);

    drawContent(p);

    drawForeground(p);
}


void PlotterBase::drawBackground(QPainter &p)
{
    p.fillRect(rect(), m_bg);
}


void PlotterBase::drawForeground(QPainter &p)
{
    // surrounding border
    p.setOpacity(1);
    p.setPen(m_pen);
    p.setBrush(Qt::NoBrush);
    p.drawRect(rect().adjusted(0,0,-1,-1));
}


void PlotterBase::drawTitle(QPainter &p)
{
    if (!m_title.isEmpty())
    {
        QRect titleRect(rect());
        titleRect.setBottom(dataRect().top()-1);

        p.setOpacity(1);
        p.setPen(m_titlePen);
        p.setFont(m_titleFont);
        p.drawText(titleRect, Qt::AlignCenter, m_title);
    }
}


void PlotterBase::drawAxes(QPainter &p)
{
    if (m_axisX)
        m_axisX->draw(p);

    if (m_axisY)
        m_axisY->draw(p);
}


QString PlotterBase::formattedValue(double value) const
{
    if (m_textFormat.isEmpty())
    {
        return QString::number(value);
    }

    return m_textFormat.arg(value);
}


void PlotterBase::setIndexUnderMouse(const QModelIndex& index)
{
    if (m_indexUnderMouse != index)
    {
        m_indexUnderMouse = index;

        //if (index.isValid())
            emit entered(index);
    }
}


} // namespace
