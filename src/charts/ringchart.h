#ifndef RINGCHART_H
#define RINGCHART_H


#include "ringplotbase.h"


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
class RingChart : public RingPlotBase
{
    Q_OBJECT

public:
    RingChart(QWidget *parent = 0);

protected:
    virtual void drawContent(QPainter &p);

    virtual void drawSegment(QPainter &p, const QRect& pieRect,
                               const QModelIndex &index, double value,
                               double angle1, double angle2,
                               bool isHighlighted);

    virtual void drawValue(QPainter &p, const QRect& pieRect,
                               const QModelIndex &index, double value,
                               double angle1, double angle2,
                               bool isHighlighted);
};


}


#endif
