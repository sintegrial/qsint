#include "barchartplotter.h"
#include "axisbase.h"

// temp
#include "stackedbarpainter.h"
#include "columnbarpainter.h"
#include "trendpainter.h"


namespace QSint
{


BarChartPlotter::BarChartPlotter(QWidget *parent) :
    PlotterBase(parent)
{
    m_axisX = new AxisBase(Qt::Horizontal, this);
    m_axisY = new AxisBase(Qt::Vertical, this);

    setBarType(Stacked);

    m_axisX->setType(AxisBase::AxisModel);

    setBarSize(-INT_MAX, INT_MAX);
    setBarScale(0.5);
    setBarOpacity(1.0);

    setZeroLinePen(QPen(Qt::white));
}


void BarChartPlotter::setBarType(BarChartType type)
{
    m_type = type;
}


void BarChartPlotter::setBarSize(int min, int max)
{
    m_barsize_min = qMax(min, 0);
    m_barsize_max = qMax(min, max);
}


void BarChartPlotter::setBarScale(double scale)
{
    if (scale < 0.1)
        m_scale = 0.1;
    else
        m_scale = qMin(scale, 1.0);
}


void BarChartPlotter::setBarOpacity(double value)
{
    if (value < 0.0)
        m_opacity = 0;
    else
        m_opacity = qMin(value, 1.0);
}


void BarChartPlotter::setZeroLinePen(const QPen &pen)
{
    m_zeroLinePen = pen;
}


void BarChartPlotter::drawContent(QPainter &p)
{
    if (!m_model || !m_axisX || !m_axisY)
        return;

    int p_start, p_end;
    m_axisX->calculatePoints(p_start, p_end);

    // draw zero line
    int p_y = m_axisY->toView(0);

    p.setPen(m_zeroLinePen);
    p.drawLine(p_start, p_y, p_end, p_y);

    int count = m_model->columnCount();
    if (!count)
        return;

    int row_count = m_model->rowCount();
    if (!row_count)
        return;

    int p_offs = double(p_end - p_start) / count;

    int bar_size = p_offs * m_scale;

    if (bar_size > m_barsize_max)
        bar_size = qMin(m_barsize_max, p_offs);
    else if (bar_size < m_barsize_min)
        bar_size = qMin(m_barsize_min, p_offs);


    switch (m_type)
    {
    case Stacked:
        StackedBarPainter::draw(this, p, count, row_count, p_start, p_offs, bar_size);
        break;

    case Columns:
        ColumnBarPainter::draw(this, p, count, row_count, p_start, p_offs, bar_size);
        break;

    case Trend:
        TrendPainter::draw(this, p, count, row_count, p_start, p_offs, bar_size);
        break;

    } // switch
}


void BarChartPlotter::drawSegment(QPainter &p, QRect rect,
                                  const QModelIndex &index, double /*value*/,
                                  bool isHighlighted) const
{
    if (isHighlighted)
    {
        p.setPen(highlightPen());
        p.setBrush(highlightBrush());
    }
    else
    {
        QVariant v_brush(index.data(Qt::BackgroundRole));
        if (v_brush.isValid())
            p.setBrush(qvariant_cast<QBrush>(v_brush));
        else
            p.setBrush(qvariant_cast<QBrush>(model()->headerData(index.row(), Qt::Vertical, Qt::BackgroundRole)));

        p.setPen(itemPen());
    }

    if (barType() == Trend)
    {
        p.drawEllipse(rect.topLeft(), 3, 3);
        return;
    }

    p.drawRect(rect);
}


void BarChartPlotter::drawValue(QPainter &p, QRect rect,
                                  const QModelIndex &index, double value,
                                  bool isHighlighted) const
{
    int flags = Qt::AlignCenter;

    QString text = formattedValue(value);

    QRect textRect(p.fontMetrics().boundingRect(text));

    switch (barType())
    {
        case Columns:
            if (value < 0)
            {
                flags = Qt::AlignHCenter | Qt::AlignTop;
                rect.setTop(rect.bottom() + 4);
                rect.setHeight(textRect.height());
            }
            else
            {
                flags = Qt::AlignHCenter | Qt::AlignBottom;
                rect.setTop(rect.top() - textRect.height() - 4);
                rect.setHeight(textRect.height());
            }

            if (rect.width() < textRect.width() + 4)
                rect.setWidth(textRect.width() + 4);

            if (isHighlighted)
            {
                flags = Qt::AlignCenter;
                QRect frameRect = drawHighlightedValueFrame(p, rect, textRect);
                drawValueText(p, frameRect, flags, true, index, text);
            }
            else if (m_valuesAlwaysShown)
            {
               drawValueText(p, rect, flags, false, index, text);
            }

            break;

        case Stacked:
            if (textRect.height() > rect.height() || textRect.width() > rect.width())
            {
                if (isHighlighted)
                {
                    QRect frameRect = drawHighlightedValueFrame(p, rect, textRect);
                    drawValueText(p, frameRect, flags, true, index, text);
                }
            }
            else if (m_valuesAlwaysShown || isHighlighted)
            {
                drawValueText(p, rect, flags, isHighlighted, index, text);
            }

            break;

        case Trend:
        {
            int rectWidth = rect.width();
            rect.setSize(textRect.size());
            rect.moveLeft(rect.left() + (rectWidth - textRect.width()) /2);

            rect.moveTop(rect.top() - rect.height()/2);
            if (value < 0)
                rect.moveTop(rect.top() + rect.height());
            else
                rect.moveTop(rect.top() - rect.height());

            if (rect.width() < textRect.width() + 4)
            {
                rect.setWidth(textRect.width() + 4);
                rect.moveLeft(rect.left() - 2);
            }

            if (isHighlighted)
            {
                drawHighlightedValueFrame(p, rect, textRect);
            }

            if (m_valuesAlwaysShown || isHighlighted)
            {
                drawValueText(p, rect, flags, isHighlighted, index, text);
            }

            break;
        }

        default:;
    }

}


void BarChartPlotter::drawValueText(QPainter &p, const QRect &rect, int flags, bool isHighlighted, const QModelIndex &index, const QString &text) const
{
    if (isHighlighted)
    {
        p.setPen(QPen(highlightTextColor()));
    }
    else
    {
        QVariant v_pen(index.data(Qt::ForegroundRole));
        if (v_pen.isValid())
            p.setPen(qvariant_cast<QColor>(v_pen));
        else
            p.setPen(qvariant_cast<QColor>(model()->headerData(index.row(), Qt::Vertical, Qt::ForegroundRole)));
    }

    p.drawText(rect, flags, text);
}


QRect BarChartPlotter::drawHighlightedValueFrame(QPainter &p, const QRect &rect, const QRect &textRect) const
{    
    QRect backRect(textRect.adjusted(-3,-3,3,3));
    backRect.moveLeft(rect.center().x() - backRect.width()/2);
    backRect.moveTop(rect.center().y() - backRect.height()/2);

    p.setPen(highlightPen());
    p.setBrush(highlightBrush());
    p.drawRect(backRect);

    return backRect;
}


void BarPainter::drawBarItem(QPainter &p, QRect rect,
                                              const QPen &pen, const QBrush &brush,
                                              const QModelIndex &/*index*/, double /*value*/)
{
    p.setPen(pen);
    p.setBrush(brush);
    p.drawRect(rect);
}


void BarPainter::drawValueText(QPainter &p, QRect rect, int flags,
                                                const QPen &pen, const QBrush &brush,
                                                const QModelIndex &index, double /*value*/)
{
    p.setPen(pen);
    p.setBrush(brush);
    p.drawText(rect, flags, index.data(Qt::DisplayRole).toString());
}


} // namespace
