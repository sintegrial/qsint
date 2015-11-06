#include "trendpainter.h"
#include "axisbase.h"


namespace QSint
{


void TrendPainter::draw(
    BarChartPlotter *plotter,
    QPainter &p,
    int count,
    int row_count,
    int p_start,
    int p_offs,
    int /*bar_size*/)
{
    bool isUnderMouse = false;
    double valueHl;
    QModelIndex indexHl;
    QRect rectHl;

    p.save();
    p.setRenderHint(QPainter::Antialiasing);

    p.setOpacity(plotter->barOpacity());

    p.setFont(plotter->font());

    for (int j = 0; j < row_count; j++)
    {
        QPen pen(qvariant_cast<QColor>(plotter->model()->headerData(j, Qt::Vertical, Qt::ForegroundRole)));
        QBrush brush(qvariant_cast<QBrush>(plotter->model()->headerData(j, Qt::Vertical, Qt::BackgroundRole)));

        QPolygon points;

        for (int i = 0; i < count; i++)
        {
            const QModelIndex index(plotter->model()->index(j, i));
            double value = index.data(Qt::EditRole).toDouble();

            int x = p_start + p_offs*i + p_offs/2;
            int y = plotter->axisY()->toView(value);
            QRect itemRect(x,y,1,1);

            points.append(itemRect.topLeft());

            // check for object under mouse
            if (!isUnderMouse && !plotter->mousePos().isNull() && QRect(x-3, y-3, 7, 7).contains(plotter->mousePos()))
            {
                isUnderMouse = true;
                valueHl = value;
                indexHl = index;
                rectHl = itemRect;
            }

            if (index == indexHl && plotter->isHighlightEnabled())
                continue;

            plotter->drawValue(p, itemRect, index, value, false);
        }

        p.setPen(QPen(brush, 2));
        p.drawPolyline(points);

        //p.setPen(pen);
        //p.setBrush(brush);
        for (int i = 0; i < count; i++)
        {
            const QModelIndex index(plotter->model()->index(j, i));
            if (index == indexHl && plotter->isHighlightEnabled())
                continue;

            double value = index.data(Qt::EditRole).toDouble();
            plotter->drawSegment(p, QRect(points.at(i), QSize(1,1)), index, value, false);

            //p.drawEllipse(points.at(i), 3, 3);
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

    p.restore();
}


}
