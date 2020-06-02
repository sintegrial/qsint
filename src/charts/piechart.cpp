#include <qmath.h>

#include "piechart.h"


namespace QSint
{


PieChart::PieChart(QWidget *parent) :
    RingPlotBase(parent)
{
    m_index = 0;
}


void PieChart::setActiveIndex(int index)
{
    if (m_index == index)
        return;

    m_index = 0;

    scheduleUpdate();

    if (!m_model)
        return;

    if (index >= 0 && index < m_model->columnCount())
        m_index = index;
}


void PieChart::setActiveIndex(const QModelIndex &index)
{
    if (index.isValid())
        setActiveIndex(index.column());
}


void PieChart::drawData(QPainter &p, int innerRadius, int outerRadius, const QRect& pieRect)
{
	// check if need to draw highlight
	bool checkHighlight = false;
	double mouseAngle = 0;

	// check if we're inside piechart at all
	if (!m_mousePos.isNull() && pieRect.contains(m_mousePos))
	{
		// Determine the distance from the center point of the pie chart.
		double cx = m_mousePos.x() - pieRect.center().x();
		double cy = pieRect.center().y() - m_mousePos.y();
		double mouseRadius = pow(pow(cx, 2) + pow(cy, 2), 0.5);
		if (!(mouseRadius <= innerRadius || mouseRadius >= outerRadius))
		{
			// Determine the angle of the point.
			mouseAngle = (180 / M_PI) * acos(cx / mouseRadius);
			if (cy < 0)
				mouseAngle = 360 - mouseAngle;

			checkHighlight = true;
		}
	}

	drawRing(p, pieRect.center(), m_index, innerRadius, outerRadius, checkHighlight, mouseAngle);
}


void PieChart::drawSegment(QPainter &p, const QRect& pieRect,
                           const QModelIndex &index, double /*value*/,
                           double angle1, double angle2,
                           bool isHighlighted)
{
    int r = index.row();

    if (isHighlighted)
    {
        p.setPen(m_hlPen);
        p.setBrush(m_hlBrush);

        p.drawPie(pieRect, int(angle1*16), int(angle2*16));
    }
    else
    {
        p.setPen(m_itemPen);
		p.setBrush(brushFromIndex(index));

        p.drawPie(pieRect, int(angle1*16), int(angle2*16));
    }
}


}
