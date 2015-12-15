#include "barpainter.h"
#include "barchartplotter.h"


namespace QSint
{


void BarPainter::drawValueText(
	BarChartPlotter *plotter, 
	QPainter &p, 
	const QRect &rect, 
	int flags, 
	bool isHighlighted, 
	const QModelIndex &index, 
	const QString &text) const
{
	if (isHighlighted)
	{
		p.setPen(QPen(plotter->highlightTextColor()));
	}
	else
	{
		QVariant v_pen(index.data(Qt::ForegroundRole));
		if (v_pen.isValid())
			p.setPen(qvariant_cast<QColor>(v_pen));
		else
			p.setPen(qvariant_cast<QColor>(index.model()->headerData(index.row(), Qt::Vertical, Qt::ForegroundRole)));
	}

	p.drawText(rect, flags, text);
}


QRect BarPainter::drawHighlightedValueFrame(
	BarChartPlotter *plotter,
	QPainter &p, const QRect &rect, const QRect &textRect) const
{    
	QRect backRect(textRect.adjusted(-3,-3,3,3));
	backRect.moveLeft(rect.center().x() - backRect.width()/2);
	backRect.moveTop(rect.center().y() - backRect.height()/2);

	p.setPen(plotter->highlightPen());
	p.setBrush(plotter->highlightBrush());
	p.drawRect(backRect);

	return backRect;
}


void BarPainter::drawSegment(
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

	p.drawRect(rect);
}


} //ns
