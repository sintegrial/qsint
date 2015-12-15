#ifndef PIECHART_H
#define PIECHART_H


#include "ringplotbase.h"


namespace QSint
{


/**
    \brief Class representing a piechart widget.
    \since 0.2.1

    \image html PieChart.png An example of PieChart

    PieChart represents single column of the model as a pie chart diagram.
    Use setActiveIndex() method to choose the active column within the model.
*/
class PieChart : public RingPlotBase
{
    Q_OBJECT

public:
    PieChart(QWidget *parent = 0);

public Q_SLOTS:
    /// Sets active column to the \a index.
    void setActiveIndex(int index);
    /// Sets active column to the \a index.column().
    void setActiveIndex(const QModelIndex &index);

protected:
    virtual void drawContent(QPainter &p);

    /** Draws a signle pie chart segment using QPainter \a p.
      Chart is to be drawn in the rectangle \a pieRect.
      Current model index of the segment in \a index, current value is \a value.
      \a angle1 and \a angle2 are start and end angles of the segment (in gradus).
      \a isHighlighted is true when the segment is highlighted.
    */
    virtual void drawSegment(QPainter &p, const QRect& pieRect,
                               const QModelIndex &index, double value,
                               double angle1, double angle2,
                               bool isHighlighted);

    /** Draws value signle pie chart segment using QPainter \a p.
      Chart is to be drawn in the rectangle \a pieRect.
      Current model index of the segment in \a index, current value is \a value.
      \a angle1 and \a angle2 are start and end angles of the segment (in gradus).
      \a isHighlighted is true when the segment is highlighted.
    */
    virtual void drawValue(QPainter &p, const QRect& pieRect,
                               const QModelIndex &index, double value,
                               double angle1, double angle2,
                               bool isHighlighted);
protected:
    int m_index;
};


}


#endif
