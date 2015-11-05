#ifndef PAINTSCHEME_H
#define PAINTSCHEME_H


#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtGui/QFont>
#include <QtGui/QColor>


namespace QSint
{


class PaintScheme
{
public:
    PaintScheme();

    QPen basePen;
    QBrush baseBrush;

    QFont axisPen;
    QFont axisTextFont;
    QColor axisTextColor;

    QFont itemPen;
    QBrush itemBrush;
    QFont itemTextFont;
    QColor itemTextColor;

    QFont itemHighlightPen;
    QBrush itemHighlightBrush;
    QColor itemTextHighlightColor;
};


}


#endif // PAINTSCHEME_H
