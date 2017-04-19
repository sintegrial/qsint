#include <qmath.h>

#include "ringchart.h"


namespace QSint
{


RingChart::RingChart(QWidget *parent) :
    RingPlotBase(parent)
{
}


void RingChart::drawContent(QPainter &p)
{
    QRect dr(dataRect());

    int w = dr.width() - m_margin*2;
    int h = dr.height() - m_margin*2;

    int wh = qMin(w,h);
    int wh2 = wh / 2;

    int dx2 = (w - wh) / 2;
    int dy2 = dr.top() + (h - wh) / 2;

    QRect pieRect = QRect(dx2+m_margin, dy2+m_margin, wh, wh);

    //p.drawEllipse(pieRect);

    if (!m_model)
        return;

    int row_count = m_model->rowCount();
    if (!row_count)
        return;

    int count = m_model->columnCount();
    if (!count)
        return;

    // check if need to draw highlight
    bool checkHighlight = false;
    double mouseAngle = 0, mouseRadius = 0;

    // check if we're inside piechart at all
    if (!m_mousePos.isNull() && pieRect.contains(m_mousePos))
    {
        // Determine the distance from the center point of the pie chart.
        double cx = m_mousePos.x() - dx2 - wh2;
        double cy = dy2 + wh2 - m_mousePos.y();
        mouseRadius = pow(pow(cx, 2) + pow(cy, 2), 0.5);
        if (!(mouseRadius == 0 || mouseRadius > wh2)){
            // Determine the angle of the point.
            mouseAngle = (180 / M_PI) * acos(cx / mouseRadius);
            if (cy < 0)
                mouseAngle = 360 - mouseAngle;

            checkHighlight = true;
        }
    }

	// TODO: ^^^ same as by Piechart - merge ^^^

    // draw rings
    p.setFont(m_font);

	for (int ring = count-1; ring >= 0; ring--)
	{
		// inner radius of the ring
		int r1 = wh2 * ring / count;

		// outer radius of the ring
		int r2 = wh2 * (ring + 1) / count;

		// check if we are NOT between rings
		bool ringHighlight = checkHighlight;
		if (ringHighlight && (mouseRadius <= r1 || mouseRadius >= r2))
			ringHighlight = false;

		drawRing(p, pieRect.center(), ring, r1, r2, ringHighlight, mouseAngle);
	}

}


void RingChart::drawSegment(QPainter &p, const QRect& pieRect,
                           const QModelIndex &index, double /*value*/,
                           double angle1, double angle2,
                           bool isHighlighted)
{
    int r = index.row();

    p.setPen(m_itemPen);

    QBrush brush(qvariant_cast<QBrush>(m_model->headerData(r, Qt::Vertical, Qt::BackgroundRole)));
    p.setBrush(brush);

    p.drawPie(pieRect, int(angle1*16), int(angle2*16));

	// draw over if highlighted
    if (isHighlighted)
    {
        p.setPen(m_hlPen);
        p.setBrush(m_hlBrush);

        p.drawPie(pieRect, int(angle1*16), int(angle2*16));
    }
}


void RingChart::drawValue(QPainter &p, const QRect& pieRect,
                           const QModelIndex &index, double value,
                           double angle1, double angle2,
                           bool isHighlighted)
{
    // text (angle CCW in radians)
    double cr = pieRect.height()/2 - 20;
    double textAngle = (360 - angle1 - angle2/2) * M_PI / 180;
    double tx = cr * cos(textAngle) + pieRect.center().x();
    double ty = cr * sin(textAngle) + pieRect.center().y();

    if (isHighlighted)
    {
        p.setPen(QPen(m_hlTextColor));
    }
    else
    {
        QPen pen(qvariant_cast<QColor>(m_model->headerData(index.row(), Qt::Vertical, Qt::ForegroundRole)));
        p.setPen(pen);
    }

	p.drawText(tx, ty, formattedValue(value, index));
}


}

