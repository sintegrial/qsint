#include "stackedbarpainter.h"
#include "axisbase.h"


namespace QSint
{


void StackedBarPainter::draw(
    BarChartPlotter *plotter,
    QPainter &p,
    int count,
    int row_count,
    int p_start,
    int p_offs,
    int bar_size)
{
    bool isUnderMouse = false;
    double valueHl;
    QModelIndex indexHl;
    QRect rectHl;

    for (int i = 0; i < count; i++)
    {
        int p_d = p_start + p_offs*i + (p_offs-bar_size)/2;

        double acc_value = 0;
        int p_y = plotter->axisY()->toView(0);

        double neg_value = 0;
        int p_ny = p_y;

        p.setOpacity(plotter->barOpacity());

        for (int j = 0; j < row_count; j++)
        {
            QRect itemRect;

            const QModelIndex index(plotter->model()->index(j, i));
            double value = index.data(Qt::EditRole).toDouble();
            if (value < 0)
            {
                neg_value += value;

                int p_h = plotter->axisY()->toView(neg_value);

                itemRect = QRect(p_d, p_ny, bar_size, p_h-p_ny);

                p_ny = p_h;
            }
            else
            {
                acc_value += value;

                int p_h = plotter->axisY()->toView(acc_value);

                itemRect = QRect(p_d, p_h, bar_size, p_y-p_h);

                p_y = p_h;
            }

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

