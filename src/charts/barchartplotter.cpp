#include "barchartplotter.h"
#include "axisbase.h"


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
        QVariant v_brush(model()->data(index, Qt::BackgroundRole));
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
        QVariant v_pen(model()->data(index, Qt::ForegroundRole));
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


void BarChartPlotter::BarPainter::drawBarItem(QPainter &p, QRect rect,
                                              const QPen &pen, const QBrush &brush,
                                              const QModelIndex &/*index*/, double /*value*/)
{
    p.setPen(pen);
    p.setBrush(brush);
    p.drawRect(rect);
}


void BarChartPlotter::BarPainter::drawValueText(QPainter &p, QRect rect, int flags,
                                                const QPen &pen, const QBrush &brush,
                                                const QModelIndex &index, double /*value*/)
{
    p.setPen(pen);
    p.setBrush(brush);
    //p.drawText(rect, flags, QString::number(value));
    p.drawText(rect, flags, index.data(Qt::DisplayRole).toString());
}


void BarChartPlotter::StackedBarPainter::draw(
    BarChartPlotter *plotter,
    QPainter &p,
    int count,
    int row_count,
    int p_start,
    int p_offs,
    int bar_size)
{
    bool isUnderMouse = false;
    double valueHl;
    QModelIndex indexHl;
    QRect rectHl;

    for (int i = 0; i < count; i++)
    {
        int p_d = p_start + p_offs*i + (p_offs-bar_size)/2;

        double acc_value = 0;
        int p_y = plotter->axisY()->toView(0);

        double neg_value = 0;
        int p_ny = p_y;

        p.setOpacity(plotter->barOpacity());

        for (int j = 0; j < row_count; j++)
        {
            QRect itemRect;

            const QModelIndex index(plotter->model()->index(j, i));
            double value = plotter->model()->data(index, Qt::EditRole).toDouble();
            if (value < 0)
            {
                neg_value += value;

                int p_h = plotter->axisY()->toView(neg_value);

                itemRect = QRect(p_d, p_ny, bar_size, p_h-p_ny);

                p_ny = p_h;
            }
            else
            {
                acc_value += value;

                int p_h = plotter->axisY()->toView(acc_value);

                itemRect = QRect(p_d, p_h, bar_size, p_y-p_h);

                p_y = p_h;
            }

            // check for highlight
            if (!isUnderMouse && !plotter->mousePos().isNull() && itemRect.contains(plotter->mousePos()))
            {
                isUnderMouse = true;
                valueHl = value;
                indexHl = index;
                rectHl = itemRect;
            }

            // do not draw if highlighted
            if (plotter->isHighlightEnabled() && index == indexHl)
                continue;

            plotter->drawSegment(p, itemRect, index, value, false);
            plotter->drawValue(p, itemRect, index, value, false);
        }
    }

    if (isUnderMouse)
    {
        plotter->setIndexUnderMouse(indexHl);

        if (plotter->isHighlightEnabled())
        {
            plotter->drawSegment(p, rectHl, indexHl, valueHl, true);
            plotter->drawValue(p, rectHl, indexHl, valueHl, true);
        }
    }
    else
        plotter->setIndexUnderMouse(QModelIndex());
}


void BarChartPlotter::ColumnBarPainter::draw(
    BarChartPlotter *plotter,
    QPainter &p,
    int count,
    int row_count,
    int p_start,
    int p_offs,
    int bar_size)
{
    int single_bar_size = bar_size/row_count;
    if (!single_bar_size)
        return;

    bool isUnderMouse = false;
    double valueHl;
    QModelIndex indexHl;
    QRect rectHl;

    for (int i = 0; i < count; i++)
    {
        int p_d = p_start + p_offs*i + (p_offs-bar_size)/2;

        int p_y = plotter->axisY()->toView(0);

        p.setOpacity(plotter->barOpacity());

        for (int j = 0; j < row_count; j++)
        {
            const QModelIndex index(plotter->model()->index(j, i));
            double value = plotter->model()->data(index, Qt::EditRole).toDouble();

            int p_h = plotter->axisY()->toView(value);

            QRect itemRect;

            if (value < 0)
            {
                itemRect = QRect(p_d, p_y, single_bar_size, p_h-p_y);
            }
            else
            {
                itemRect = QRect(p_d, p_h, single_bar_size, p_y-p_h);
            }

            p_d += single_bar_size;

            // check for highlight
            if (!isUnderMouse && !plotter->mousePos().isNull() && itemRect.contains(plotter->mousePos()))
            {
                isUnderMouse = true;
                valueHl = value;
                indexHl = index;
                rectHl = itemRect;
            }

            // do not draw if highlighted
            if (plotter->isHighlightEnabled() && index == indexHl)
                continue;

            plotter->drawSegment(p, itemRect, index, value, false);
            plotter->drawValue(p, itemRect, index, value, false);
        }
    }

    if (isUnderMouse)
    {
        plotter->setIndexUnderMouse(indexHl);

        if (plotter->isHighlightEnabled())
        {
            plotter->drawSegment(p, rectHl, indexHl, valueHl, true);
            plotter->drawValue(p, rectHl, indexHl, valueHl, true);
        }
    }
    else
        plotter->setIndexUnderMouse(QModelIndex());
}


void BarChartPlotter::TrendPainter::draw(
    BarChartPlotter *plotter,
    QPainter &p,
    int count,
    int row_count,
    int p_start,
    int p_offs,
    int /*bar_size*/)
{
    bool isUnderMouse = false;
    double valueHl;
    QModelIndex indexHl;
    QRect rectHl;

    p.save();
    p.setRenderHint(QPainter::Antialiasing);

    p.setOpacity(plotter->barOpacity());

    p.setFont(plotter->font());

    for (int j = 0; j < row_count; j++)
    {
        QPen pen(qvariant_cast<QColor>(plotter->model()->headerData(j, Qt::Vertical, Qt::ForegroundRole)));
        QBrush brush(qvariant_cast<QBrush>(plotter->model()->headerData(j, Qt::Vertical, Qt::BackgroundRole)));

        QPolygon points;

        for (int i = 0; i < count; i++)
        {
            const QModelIndex index(plotter->model()->index(j, i));
            double value = plotter->model()->data(index, Qt::EditRole).toDouble();

            int x = p_start + p_offs*i + p_offs/2;
            int y = plotter->axisY()->toView(value);
            QRect itemRect(x,y,1,1);

            points.append(itemRect.topLeft());

            // check for object under mouse
            if (!isUnderMouse && !plotter->mousePos().isNull() && QRect(x-3, y-3, 7, 7).contains(plotter->mousePos()))
            {
                isUnderMouse = true;
                valueHl = value;
                indexHl = index;
                rectHl = itemRect;
            }

            if (index == indexHl && plotter->isHighlightEnabled())
                continue;

            plotter->drawValue(p, itemRect, index, value, false);
        }

        p.setPen(QPen(brush, 2));
        p.drawPolyline(points);

        //p.setPen(pen);
        //p.setBrush(brush);
        for (int i = 0; i < count; i++)
        {
            const QModelIndex index(plotter->model()->index(j, i));
            if (index == indexHl && plotter->isHighlightEnabled())
                continue;

            double value = plotter->model()->data(index, Qt::EditRole).toDouble();
            plotter->drawSegment(p, QRect(points.at(i), QSize(1,1)), index, value, false);

            //p.drawEllipse(points.at(i), 3, 3);
        }
    }

    if (isUnderMouse)
    {
        plotter->setIndexUnderMouse(indexHl);

        if (plotter->isHighlightEnabled())
        {
            plotter->drawSegment(p, rectHl, indexHl, valueHl, true);
            plotter->drawValue(p, rectHl, indexHl, valueHl, true);
        }
    }
    else
        plotter->setIndexUnderMouse(QModelIndex());

    p.restore();
}


} // namespace
