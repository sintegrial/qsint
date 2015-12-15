#ifndef STACKEDBARPAINTER_H
#define STACKEDBARPAINTER_H

#include "barpainter.h"


namespace QSint
{


class StackedBarPainter : public BarPainter
{
public:
	virtual QModelIndex draw(
		BarChartPlotter *plotter,
		const QPoint& mousePosition,
		QPainter &p,
		int count,
		int row_count,
		int p_start,
		int p_offs,
		int bar_size) const;

	virtual void drawValue(
		BarChartPlotter *plotter,
		QPainter &p, 
		QRect rect,
		const QModelIndex &index, 
		double value,
		bool isHighlighted) const;
};


}

#endif // STACKEDBARPAINTER_H
