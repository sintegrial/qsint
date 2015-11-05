#ifndef BARCHARTPLOTTER_H
#define BARCHARTPLOTTER_H


#include "plotterbase.h"


namespace QSint
{


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
    /// Retrieves type of the plotter.
    inline BarChartType barType() const { return m_type; }

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

    virtual void drawSegment(QPainter &p, QRect rect,
                              const QModelIndex &index, double value,
                              bool isHighlighted) const;

    virtual void drawValue(QPainter &p, QRect rect,
                              const QModelIndex &index, double value,
                              bool isHighlighted) const;

    virtual void drawValueText(QPainter &p,
                               const QRect &rect,
                               int flags,
                               bool isHighlighted,
                               const QModelIndex &index,
                               const QString &text) const;

    virtual QRect drawHighlightedValueFrame(QPainter &p,
                                           const QRect &rect,
                                           const QRect &textRect) const;

    int m_barsize_min, m_barsize_max;
    double m_scale;
    double m_opacity;
    BarChartType m_type;

    QPen m_zeroLinePen;

protected:
    class BarPainter
    {
    protected:
        static void drawBarItem(QPainter &p, QRect rect,
                                 const QPen &pen, const QBrush &brush,
                                 const QModelIndex &index,
                                 double value);

        static void drawValueText(QPainter &p, QRect rect, int flags,
                                 const QPen &pen, const QBrush &brush,
                                 const QModelIndex &index,
                                 double value);
    };

    class StackedBarPainter: public BarPainter
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

    class ColumnBarPainter: public BarPainter
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

    class TrendPainter: public BarPainter
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
};


} // namespace

#endif // BARCHARTPLOTTER_H
