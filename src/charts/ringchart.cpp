#include <qmath.h>

#include "ringchart.h"


namespace QSint
{


RingChart::RingChart(QWidget *parent) :
    RingPlotBase(parent)
{
}


void RingChart::drawData(QPainter &p, int innerRadius, int outerRadius, const QRect& pieRect)
{
	int count = m_model->columnCount();
	if (count <= 0)
		return;

	// check if need to draw highlight
	bool checkHighlight = false;
	double mouseAngle = 0, mouseRadius = 0;

	// check if we're inside piechart at all
	if (!m_mousePos.isNull() && pieRect.contains(m_mousePos))
	{
		// Determine the distance from the center point of the pie chart.
		double cx = m_mousePos.x() - pieRect.center().x();
		double cy = pieRect.center().y() - m_mousePos.y();
		mouseRadius = pow(pow(cx, 2) + pow(cy, 2), 0.5);
		if (!(mouseRadius <= innerRadius || mouseRadius >= outerRadius))
		{
			// Determine the angle of the point.
			mouseAngle = (180 / M_PI) * acos(cx / mouseRadius);
			if (cy < 0)
				mouseAngle = 360 - mouseAngle;

			checkHighlight = true;
		}
	}


	// draw rings
	int dr = outerRadius - innerRadius;
	int ringSize = dr / count;
	int r1 = innerRadius;
	int r2 = outerRadius;

	for (int ring = count - 1; ring >= 0; ring--)
	{
		// inner radius of the ring
		r1 = r2 - ringSize;

		// check if we are NOT between rings
		bool ringHighlight = checkHighlight;
		if (ringHighlight && (mouseRadius <= r1 || mouseRadius >= r2))
			ringHighlight = false;

		drawRing(p, pieRect.center(), ring, r1, r2, ringHighlight, mouseAngle);

		// go next ring
		r2 = r1;
	}
}


void RingChart::drawSegment(QPainter &p, const QRect& pieRect,
                           const QModelIndex &index, double /*value*/,
                           double angle1, double angle2,
                           bool isHighlighted)
{
    p.setPen(m_itemPen);

    p.setBrush(brushFromIndex(index));

    p.drawPie(pieRect, int(angle1*16), int(angle2*16));

    // draw over if highlighted
    if (isHighlighted)
    {
        p.setPen(m_hlPen);
        p.setBrush(m_hlBrush);

        p.drawPie(pieRect, int(angle1*16), int(angle2*16));
    }
}


}

