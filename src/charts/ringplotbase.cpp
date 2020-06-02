#include "ringplotbase.h"

#include <QToolTip>
#include <qmath.h>


namespace QSint
{


RingPlotBase::RingPlotBase(QWidget *parent)
: PlotterBase(parent),
  m_showNegatives(true),
  m_margin(3),
  m_cutout(0)
{
    setAntiAliasing(true);

    m_valuesAlwaysShown = false;
}


void RingPlotBase::setMargin(int margin)
{
    if (margin < 0 || margin == m_margin)
        return;

    m_margin = margin;

    scheduleUpdate();
}


void RingPlotBase::enableNegatives(bool on)
{
    if (m_showNegatives == on)
        return;

    m_showNegatives = on;

    scheduleUpdate();
}


void RingPlotBase::setCutoutPercentage(float cutout)
{
    if (cutout < 0) cutout = 0; else
    if (cutout > 1) cutout = 1;

    if (cutout != m_cutout)
    {
        m_cutout = cutout;

		if (m_centralWidget)
			m_centralWidget->setVisible(m_cutout > 0);

        scheduleUpdate();
    }
}


void RingPlotBase::setCentralWidget(QWidget *centralWidget)
{
	if (m_centralWidget && m_centralWidget->parent() == this)
		delete m_centralWidget;

	m_centralWidget = centralWidget;
	if (m_centralWidget)
		m_centralWidget->setParent(this);

	scheduleUpdate();
}


// drawings

void RingPlotBase::drawContent(QPainter &p)
{
	QRect dr(dataRect());

	int w = dr.width() - m_margin * 2;
	int h = dr.height() - m_margin * 2;

	int wh = qMin(w, h);
	int wh2 = wh / 2;

	int dx2 = (w - wh) / 2;
	int dy2 = dr.top() + (h - wh) / 2;

	QRect pieRect = QRect(dx2 + m_margin, dy2 + m_margin, wh, wh);

	p.setBrush(m_bg);
	p.setPen(m_itemPen);
	p.drawEllipse(pieRect);

	if (!m_model)
		return;

	int row_count = m_model->rowCount();
	if (!row_count)
		return;

	int count = m_model->columnCount();
	if (!count)
		return;
	
	// draw chart
	p.setFont(font());

	// inner radius
	int r1 = 0;

	// cutout
	if (m_cutout > 0)
	{
		r1 = (float)wh2 * m_cutout;
		QRect cutRect(pieRect.center().x() - r1, pieRect.center().y() - r1, r1 * 2, r1 * 2);

		QRegion rg1(pieRect, QRegion::Ellipse);
		QRegion rg2(cutRect, QRegion::Ellipse);
		QRegion rg3 = rg1.subtracted(rg2);

		p.setClipRegion(rg3);
		p.setClipping(true);
	}

	// draw data
	int r2 = wh2;
	drawData(p, r1, r2, pieRect);

	// finish cutout
	if (m_cutout > 0)
	{
		QRect cutRect(pieRect.center().x() - r1, pieRect.center().y() - r1, r1 * 2, r1 * 2);
		drawCutout(p, cutRect);

		p.setClipping(false);

		p.setBrush(Qt::NoBrush);
		p.setPen(m_itemPen);
		p.drawEllipse(cutRect);
	}

	// draw outer ring again to restore the border
	p.setBrush(Qt::NoBrush);
	p.setPen(m_itemPen);
	p.drawEllipse(pieRect);

	// draw highlight
	if (m_indexUnderMouse.isValid())
	{
		//drawSegment(p, pieRect, m_indexUnderMouse, hoverData.valueHl, hoverData.angleHl1, hoverData.angleHl2, true);
		drawValue(p, hoverData.segmentRect, m_indexUnderMouse, hoverData.valueHl, hoverData.angleHl1, hoverData.angleHl2, true);
	}
}


void RingPlotBase::drawCutout(QPainter &p, const QRect &cutRect)
{
	if (m_centralWidget)
	{
		bool vis = !cutRect.isEmpty();
		m_centralWidget->setVisible(vis);
		if (vis)
		{
			QRect widgetRect = cutRect;
			widgetRect.setSize(cutRect.size() * 0.7);
			widgetRect.moveCenter(cutRect.center());
			m_centralWidget->resize(widgetRect.size());
			m_centralWidget->move(widgetRect.topLeft());
		}
	}
}


void RingPlotBase::drawRing(QPainter &p, const QPoint &center, int ring, int /*radius1*/, int radius2, bool checkHighlight, double mouseAngle)
{
    int row_count = m_model->rowCount();

    // calculate segments
    double totalValue = 0;

    for (int r = 0; r < row_count; r++)
    {
        const QModelIndex index(m_model->index(r, ring));
		//double value = m_model->data(index).toDouble();
		double value = valueFromIndex(index);

        if (value > 0.0)
            totalValue += value;
        else
            if (m_showNegatives)
                totalValue += -value;
    }

    // draw segments
    double startAngle = 0.0;
    bool isHighlighted = false;
    QModelIndex indexHl;

    // outer rect
    QRect pieRect(center.x() - radius2, center.y() - radius2, radius2 * 2, radius2 * 2);

    if (totalValue <= 0)
    {
        p.setBrush(m_bg);
        p.setPen(m_itemPen);
        p.drawEllipse(pieRect);
    }
    else
    for (int r = 0; r < row_count; r++)
    {
        const QModelIndex index(m_model->index(r, ring));
        //double value = m_model->data(index).toDouble();
		double value = valueFromIndex(index);

        if (value > 0.0 || m_showNegatives)
        {
            double angle = 360.0;
            if (totalValue > 0)
                angle = 360 * qAbs(value) / totalValue;

            if (checkHighlight && startAngle <= mouseAngle && mouseAngle <= (startAngle + angle))
            {
                isHighlighted = true;
				hoverData.angleHl1 = startAngle;
				hoverData.angleHl2 = angle;
				hoverData.valueHl = value;
				hoverData.segmentRect = pieRect;
                indexHl = index;
            }
            else
            {
                drawSegment(p, pieRect, index, value, startAngle, angle, false);
                //drawValue(p, pieRect, index, value, startAngle, angle, false);
            }

            startAngle += angle;
        }
    }

    // highlight to be drawn over the other segments
    if (isHighlighted)
    {
        setIndexUnderMouse(indexHl);

		drawSegment(p, hoverData.segmentRect, m_indexUnderMouse, hoverData.valueHl, hoverData.angleHl1, hoverData.angleHl2, true);
		//drawValue(p, pieRect, m_indexUnderMouse, hoverData.valueHl, hoverData.angleHl1, hoverData.angleHl2, true);
    }
}


void RingPlotBase::drawValue(QPainter &p, const QRect& segmentRect,
	const QModelIndex &index, double value,
	double angle1, double angle2,
	bool isHighlighted)
{
	// text (angle CCW in radians)
	//float cr = segmentRect.height() / 4 + segmentRect.height() / 8;
	float cr = segmentRect.height() / 2 - 20;
	float textAngle = (360 - angle1 - angle2 / 2) * M_PI / 180;
	int tx = cr * cos(textAngle) + segmentRect.center().x();
	int ty = cr * sin(textAngle) + segmentRect.center().y();

	QString text = QString("%1: %2")
		.arg(textFromIndex(index))
		.arg(formattedValue(value, index));

	QFontMetrics fm(font());
	QRect r = fm.boundingRect(text);
	r.moveCenter(QPoint(tx, ty));

	p.setBrush(m_hlBrush);
	p.setPen(m_hlPen);
	p.drawRoundedRect(r.adjusted(-5, -5, 5, 5), 4, 4);
	p.drawText(r.adjusted(0, 0, 5, 5), text);
}


}
