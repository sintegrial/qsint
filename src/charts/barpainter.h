#pragma once

#include <QtGui/QPainter>


namespace QSint
{


class BarChartPlotter;


class BarPainter
{
public:
	/// Draws all the plotter items and returns index of the item under mouse.
	virtual QModelIndex draw(
		BarChartPlotter *plotter,
		const QPoint& mousePosition,
		QPainter &p,
		int count,
		int row_count,
		int p_start,
		int p_offs,
		int bar_size) const = 0;

	virtual void drawValue(
		BarChartPlotter *plotter,
		QPainter &p, 
		QRect rect,
		const QModelIndex &index, 
		double value,
		bool isHighlighted) const = 0;

protected: 
	virtual void drawValueText(
		BarChartPlotter *plotter,
		QPainter &p,
		const QRect &rect,
		int flags,
		bool isHighlighted,
		const QModelIndex &index,
		const QString &text) const;

	virtual QRect drawHighlightedValueFrame(
		BarChartPlotter *plotter,
		QPainter &p,
		const QRect &rect,
		const QRect &textRect) const;

	virtual void drawSegment(
		BarChartPlotter *plotter,
		QPainter &p, 
		QRect rect,
		const QModelIndex &index, 
		double value,
		bool isHighlighted) const;
};


}

