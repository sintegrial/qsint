#include "columnbarpainter.h"
#include "axisbase.h"
#include "barchartplotter.h"


namespace QSint
{


QModelIndex ColumnBarPainter::draw(
    BarChartPlotter *plotter,
	const QPoint& mousePosition,
    QPainter &p,
    int count,
    int row_count,
    int p_start,
    int p_offs,
    int bar_size) const
{
	if (row_count <= 0)
		return QModelIndex();

    int single_bar_size = bar_size / row_count;
    if (!single_bar_size)
        return QModelIndex();

    bool isUnderMouse = false;
    double valueHl = 0.0;
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
            double value = index.data(Qt::EditRole).toDouble();

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
            if (!isUnderMouse && !mousePosition.isNull() && itemRect.contains(mousePosition))
            {
                isUnderMouse = true;
                valueHl = value;
                indexHl = index;
                rectHl = itemRect;
            }

            // do not draw if highlighted
            if (plotter->isHighlightEnabled() && index == indexHl)
                continue;

            drawSegment(plotter, p, itemRect, index, value, false);
            drawValue(plotter, p, itemRect, index, value, false);
        }
    }

    if (isUnderMouse)
    {
        if (plotter->isHighlightEnabled())
        {
            drawSegment(plotter, p, rectHl, indexHl, valueHl, true);
            drawValue(plotter, p, rectHl, indexHl, valueHl, true);
        }

		// item under mouse found
		return indexHl;
	}

	// no item under mouse
	return QModelIndex();
}


void ColumnBarPainter::drawValue(
	BarChartPlotter *plotter, 
	QPainter &p, 
	QRect rect,
	const QModelIndex &index, 
	double value,
	bool isHighlighted) const
{
	int flags = Qt::AlignCenter;

	QString text = plotter->formattedValue(value, index);

	QRect textRect(p.fontMetrics().boundingRect(text));

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
		QRect frameRect = drawHighlightedValueFrame(plotter, p, rect, textRect);
		drawValueText(plotter, p, frameRect, flags, true, index, text);
	}
	else if (plotter->valuesAlwaysShown())
	{
		drawValueText(plotter, p, rect, flags, false, index, text);
	}
}


}

