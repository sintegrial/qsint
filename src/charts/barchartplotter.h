#ifndef BARCHARTPLOTTER_H
#define BARCHARTPLOTTER_H


#include "plotterbase.h"


namespace QSint
{


// forwards (for GCC)
class BarPainter;
class StackedBarPainter;
class ColumnBarPainter;
class TrendPainter;


/**
    \brief Class representing a barchart plotting widget.
    \since 0.2.1

    \image html StackedChart.png An example of BarChartPlotter with \a Stacked type
    \image html ColumnChart.png An example of BarChartPlotter with \a Columns type
    \image html TrendChart.png An example of BarChartPlotter with \a Trend type

    BarChartPlotter provides following types of the charts (see \a BarChartType enum):
    - Stacked bars
    - Column-based bars
    - Trends
*/
class BarChartPlotter : public PlotterBase
{
    Q_OBJECT
public:
    explicit BarChartPlotter(QWidget *parent = 0);

    // temp
    friend class BarPainter;
    friend class StackedBarPainter;
    friend class ColumnBarPainter;
    friend class TrendPainter;


    /// \brief Defines type of the chart.
    enum BarChartType
    {
        /// bar represents single model column
        Stacked,
        /// bar represents single model value
        Columns,
        /// trend-like plot
        Trend
    };

    /// Sets the plotter type to \a type.
    void setBarType(BarChartType type);

    /// Sets custom plotter painter. The previous painter will not be deleted automatically.
    /// Plotter painters can be shared between several plotter instances.
    /// \since 0.3
    void setBarPainter(BarPainter *painter);

    /// Sets minimum and maximum sizes of a single bar.
    /// Valid for \b Stacked and \b Columns plotter types.
    void setBarSize(int min, int max = INT_MAX);
    /// Retrieves minimum bar size. \sa setBarSize()
    inline int barSizeMin() const { return m_barsize_min; }
    /// Retrieves maximum bar size. \sa setBarSize()
    inline int barSizeMax() const { return m_barsize_max; }

    /** Sets scale coefficient to \a scale.
        This value defines how many space a single model column representation could get.
        It should be in ranges between 0.1 and 1.0, 0.5 is the default.
        Valid for \b Stacked and \b Columns plotter types.
     */
    void setBarScale(double scale);
    /// Retrieves bar scale coefficient. \sa setBarScale()
    inline double barScale() const { return m_scale; }

    /// Sets opacity of a single bar to \a value (should be in ranges between 0.1 and 1.0, 1.0 is the default).
    void setBarOpacity(double value);
    /// Retrieves bar opacity. \sa setBarOpacity()
    inline double barOpacity() const { return m_opacity; }


    /// Sets pen of zero line of the plotter to \a pen.
    void setZeroLinePen(const QPen &pen);
    /// Retrieves zero line pen. \sa setZeroLinePen()
    inline const QPen& zeroLinePen() const { return m_zeroLinePen; }

protected:
    virtual void drawContent(QPainter &p);

    int m_barsize_min, m_barsize_max;
    double m_scale;
    double m_opacity;
    QPen m_zeroLinePen;

    BarPainter* m_barPainter;   
};


} // namespace

#endif // BARCHARTPLOTTER_H
