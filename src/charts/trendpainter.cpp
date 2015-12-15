#include "trendpainter.h"
#include "axisbase.h"
#include "barchartplotter.h"


namespace QSint
{


QModelIndex TrendPainter::draw(
	BarChartPlotter *plotter,
	const QPoint& mousePosition,
    QPainter &p,
	int count,
	int row_count,
    int p_start,
    int p_offs,
    int /*bar_size*/) const
{
    bool isUnderMouse = false;
    double valueHl = 0.0;
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
            double value = index.data(Qt::EditRole).toDouble();

            int x = p_start + p_offs*i + p_offs/2;
            int y = plotter->axisY()->toView(value);
            QRect itemRect(x,y,1,1);

            points.append(itemRect.topLeft());

            // check for object under mouse
            if (!isUnderMouse && !mousePosition.isNull() && QRect(x-3, y-3, 7, 7).contains(mousePosition))
            {
                isUnderMouse = true;
                valueHl = value;
                indexHl = index;
                rectHl = itemRect;
            }

            if (index == indexHl && plotter->isHighlightEnabled())
                continue;

            drawValue(plotter, p, itemRect, index, value, false);
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

            double value = index.data(Qt::EditRole).toDouble();
            drawSegment(plotter, p, QRect(points.at(i), QSize(1,1)), index, value, false);

            //p.drawEllipse(points.at(i), 3, 3);
        }
    }

    if (isUnderMouse)
    {
        if (plotter->isHighlightEnabled())
        {
            drawSegment(plotter, p, rectHl, indexHl, valueHl, true);
            drawValue(plotter, p, rectHl, indexHl, valueHl, true);
        }
    }

    p.restore();

	return indexHl;
}


void TrendPainter::drawValue(
	BarChartPlotter *plotter, 
	QPainter &p, 
	QRect rect,
	const QModelIndex &index, 
	double value,
	bool isHighlighted) const
{
	int flags = Qt::AlignCenter;

	QString text = plotter->formattedValue(value);

	QRect textRect(p.fontMetrics().boundingRect(text));

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
		drawHighlightedValueFrame(plotter, p, rect, textRect);
	}

	if (plotter->valuesAlwaysShown() || isHighlighted)
	{
		drawValueText(plotter, p, rect, flags, isHighlighted, index, text);
	}
}


void TrendPainter::drawSegment(
							 BarChartPlotter *plotter,
							 QPainter &p, 
							 QRect rect,
							 const QModelIndex &index, 
							 double /*value*/,
							 bool isHighlighted) const
{
	if (isHighlighted)
	{
		p.setPen(plotter->highlightPen());
		p.setBrush(plotter->highlightBrush());
	}
	else
	{
		QVariant v_brush(index.data(Qt::BackgroundRole));
		if (v_brush.isValid())
			p.setBrush(qvariant_cast<QBrush>(v_brush));
		else
			p.setBrush(qvariant_cast<QBrush>(index.model()->headerData(index.row(), Qt::Vertical, Qt::BackgroundRole)));

		p.setPen(plotter->itemPen());
	}

	p.drawEllipse(rect.topLeft(), 3, 3);
}


}
