#include "ringplotbase.h"


namespace QSint
{


RingPlotBase::RingPlotBase(QWidget *parent)
    : PlotterBase(parent)
{
    setAntiAliasing(true);

    m_margin = 3;

    m_valuesAlwaysShown = false;
}


void RingPlotBase::setMargin(int margin)
{
    if (margin < 0 || margin == m_margin)
        return;

    m_margin = margin;

    scheduleUpdate();
}


void RingPlotBase::drawRing(QPainter &p, const QPoint &center, int ring, int /*radius1*/, int radius2, bool checkHighlight, double mouseAngle)
{
    int row_count = m_model->rowCount();

    // calculate segments
    double totalValue = 0;

    for (int r = 0; r < row_count; r++)
    {
        const QModelIndex index(m_model->index(r, ring));
        double value = m_model->data(index).toDouble();

        if (value > 0.0)
            totalValue += value;
    }

    // draw segments
    double startAngle = 0.0;
    bool isHighlighted = false;
    double angleHl1, angleHl2, valueHl;
    QModelIndex indexHl;

    // outer rect
    QRect pieRect(center.x() - radius2, center.y() - radius2, radius2 * 2, radius2 * 2);

    for (int r = 0; r < row_count; r++)
    {
        const QModelIndex index(m_model->index(r, ring));
        double value = m_model->data(index).toDouble();

        if (value > 0.0) {
            double angle = 360 * value / totalValue;



            if (checkHighlight && startAngle <= mouseAngle && mouseAngle <= (startAngle + angle))
            {
                isHighlighted = true;
                angleHl1 = startAngle;
                angleHl2 = angle;
                valueHl = value;
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

        drawSegment(p, pieRect, indexHl, valueHl, angleHl1, angleHl2, true);
        drawValue(p, pieRect, indexHl, valueHl, angleHl1, angleHl2, true);
    }
    else
        setIndexUnderMouse(QModelIndex());
}


}
