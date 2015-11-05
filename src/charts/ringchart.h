#ifndef RINGCHART_H
#define RINGCHART_H


#include "plotterbase.h"


namespace QSint
{


/**
    \brief Class representing a ringchart widget.
    \since 0.2.2

    \image html RingChart.png An example of RingChart

    RingChart represents every column of the model as a ring which consists of the segments
	with their sizes proportional to the row values.

	Negative values are not shown therefore.
*/
class RingChart : public PlotterBase
{
    Q_OBJECT

public:
    RingChart(QWidget *parent = 0);

    /// Sets margins between the widget borders and piechart to \a margin (default is 3).
    void setMargin(int margin);
    /// Retrieves current value of the margins between the widget borders and piechart.
    inline int margin() const { return m_margin; }

protected:
    virtual void drawContent(QPainter &p);

    virtual void drawRing(QPainter &p, const QPoint &center, int ring, int radius1, int radius2, bool checkHighlight, double mouseAngle);

    virtual void drawSegment(QPainter &p, const QRect& pieRect,
                               const QModelIndex &index, double value,
                               double angle1, double angle2,
                               bool isHighlighted);

    virtual void drawValue(QPainter &p, const QRect& pieRect,
                               const QModelIndex &index, double value,
                               double angle1, double angle2,
                               bool isHighlighted);
protected:
    int m_margin;
};


}


#endif
