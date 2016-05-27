#ifndef COLUMNBARPAINTER_H
#define COLUMNBARPAINTER_H

#include "barpainter.h"


namespace QSint
{


/**
 * @brief The ColumnBarPainter class implemenents default BarChartPlotter::Trend plot representation.
 * \since 0.3
 */
class ColumnBarPainter : public BarPainter
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

#endif // COLUMNBARPAINTER_H
