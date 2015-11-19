#include "colordefs.h"


namespace QSint
{


ColorList* defaultColors()
{
    static ColorList s_defaultColors;

    if (!s_defaultColors.isEmpty())
        return &s_defaultColors;

    const int step = 32;

    for (int b = 0; b <= 256; b += 16) {
        if (b == 256) b = 255;

        s_defaultColors.append(QColor(b,b,b));
    }

    for (int r = 0; r <= 256; r += step) {
        if (r == 256) r = 255;

        for (int g = 0; g <= 256; g += step) {
            if (g == 256) g = 255;

            for (int b = 0; b <= 256; b += step) {
                if (b == 256) b = 255;

                s_defaultColors.append(QColor(r,g,b));
            }
        }
    }

    return &s_defaultColors;
}

ColorList* defaultColors2()
{
    static ColorList s_defaultColors2;

    if (!s_defaultColors2.isEmpty())
        return &s_defaultColors2;

    const int step = 64;

    for (int b = 0; b <= 256; b += 16) {
        if (b == 256) b = 255;

        s_defaultColors2.append(QColor(b,b,b));
    }

    for (int r = 0; r <= 256; r += step) {
        if (r == 256) r = 255;

        for (int g = 0; g <= 256; g += step) {
            if (g == 256) g = 255;

            for (int b = 0; b <= 256; b += step) {
                if (b == 256) b = 255;

                s_defaultColors2.append(QColor(r,g,b));
            }
        }
    }

    return &s_defaultColors2;
}

ColorList* baseColors()
{
    static ColorList s_baseColors;

    if (!s_baseColors.isEmpty())
        return &s_baseColors;

    for (int i = Qt::black; i <= Qt::darkYellow; i++)
        s_baseColors.append((Qt::GlobalColor)i);

    return &s_baseColors;
}

ColorList* namedColors()
{
    static ColorList s_namedColors;

    if (!s_namedColors.isEmpty())
        return &s_namedColors;

    QStringList names = QColor::colorNames();
    for (int i = 0; i < names.size(); i++)
        s_namedColors.append(QColor(names.at(i)));

    return &s_namedColors;
}


}

