#include "columnbarpainter.h"
#include "axisbase.h"


namespace QSint
{


void ColumnBarPainter::draw(
    BarChartPlotter *plotter,
    QPainter &p,
    int count,
    int row_count,
    int p_start,
    int p_offs,
    int bar_size)
{
    int single_bar_size = bar_size/row_count;
    if (!single_bar_size)
        return;

    bool isUnderMouse = false;
    double valueHl;
    QModelIndex indexHl;
    QRect rectHl;

    for (int i = 0; i < count; i++)
    {
        int p_d = p_start + p_offs*i + (p_offs-bar_size)/2;

        int p_y = plotter->axisY()->toView(0);

        p.setOpacity(plotter->barOpacity());

        for (int j = 0; j < row_count; j++)
        {
            const QModelIndex index(plotter->model()->index(j, i));
            double value = index.data(Qt::EditRole).toDouble();

            int p_h = plotter->axisY()->toView(value);

            QRect itemRect;

            if (value < 0)
            {
                itemRect = QRect(p_d, p_y, single_bar_size, p_h-p_y);
            }
            else
            {
                itemRect = QRect(p_d, p_h, single_bar_size, p_y-p_h);
            }

            p_d += single_bar_size;

            // check for highlight
            if (!isUnderMouse && !plotter->mousePos().isNull() && itemRect.contains(plotter->mousePos()))
            {
                isUnderMouse = true;
                valueHl = value;
                indexHl = index;
                rectHl = itemRect;
            }

            // do not draw if highlighted
            if (plotter->isHighlightEnabled() && index == indexHl)
                continue;

            plotter->drawSegment(p, itemRect, index, value, false);
            plotter->drawValue(p, itemRect, index, value, false);
        }
    }

    if (isUnderMouse)
    {
        plotter->setIndexUnderMouse(indexHl);

        if (plotter->isHighlightEnabled())
        {
            plotter->drawSegment(p, rectHl, indexHl, valueHl, true);
            plotter->drawValue(p, rectHl, indexHl, valueHl, true);
        }
    }
    else
        plotter->setIndexUnderMouse(QModelIndex());
}


}

