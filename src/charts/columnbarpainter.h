#ifndef COLUMNBARPAINTER_H
#define COLUMNBARPAINTER_H

#include "barchartplotter.h"


namespace QSint
{


class ColumnBarPainter : public BarPainter
{
public:
    static void draw(BarChartPlotter *plotter,
                     QPainter &p,
                     int count,
                     int row_count,
                     int p_start,
                     int p_offs,
                     int bar_size);
};


}

#endif // COLUMNBARPAINTER_H
