#pragma once

#include <QtGui/QPainter>


namespace QSint
{


class BarChartPlotter;


class BarPainter
{
public:
	virtual void draw(
		BarChartPlotter *plotter,
		QPainter &p,
		int count,
		int row_count,
		int p_start,
		int p_offs,
		int bar_size) = 0;

	virtual void drawValue(
		BarChartPlotter *plotter,
		QPainter &p, 
		QRect rect,
		const QModelIndex &index, 
		double value,
		bool isHighlighted) const = 0;

protected: 
	virtual void drawBarItem(
		QPainter &p, 
		QRect rect,
		const QPen &pen, 
		const QBrush &brush,
		const QModelIndex &index,
		double value);

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

