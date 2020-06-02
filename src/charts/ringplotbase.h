#ifndef RINGPLOTBASE_H
#define RINGPLOTBASE_H


#include "plotterbase.h"


namespace QSint
{


class RingPlotBase : public PlotterBase
{
public:
    RingPlotBase(QWidget *parent = 0);

    /// Sets margins between the widget borders and piechart to \a margin (default is 3).
    void setMargin(int margin);
    /// Retrieves current value of the margins between the widget borders and piechart.
    inline int margin() const { return m_margin; }

    /// Enables/disables showing of negative values.
    /// \since 0.3
    void enableNegatives(bool on = true);
    /// Checks if negative values allowed (see enableNegatives()).
    /// \since 0.3
    inline bool negativesAllowed() const { return m_showNegatives; }

    /// Defines relative size of the inner cutout (0 - disabled, 1 - 100% of size).
    /// \since 0.4
    void setCutoutPercentage(float cutout);
    /// Returns relative size of the inner cutout (0 - disabled, 1 - 100% of size).
    /// \since 0.4
    inline float cutoutPercentage() const { return m_cutout; }

	/// Custom widget to be displayed in the middle (only if inner cutout > 0, see setCutoutPercentage()).
	/// If \a centralWidget is not NULL, the plot will be set to its parent automatically.
	/// \since 0.4
	void setCentralWidget(QWidget *centralWidget);
	/// Returns custom widget displayed in the middle (see setCentralWidget()).
	/// \since 0.4
	inline QWidget* centralWidget() { return m_centralWidget; }

protected:
	// override: PlotterBase
	virtual void drawContent(QPainter &p);
	
	virtual void drawData(QPainter &p, int innerRadius, int outerRadius, const QRect& pieRect) = 0;

    virtual void drawRing(QPainter &p, const QPoint &center, int ring, int radius1, int radius2, bool checkHighlight, double mouseAngle);

    virtual void drawSegment(QPainter &p, const QRect& pieRect,
                               const QModelIndex &index, double value,
                               double angle1, double angle2,
                               bool isHighlighted) = 0;

	/** Draws value of the segment using QPainter \a p.
	  Value is to be drawn in the rectangle \a pieRect.
	  Current model index of the segment in \a index, current value is \a value.
	  \a angle1 and \a angle2 are start and end angles of the segment (in degrees).
	  \a isHighlighted is true when the segment is highlighted.
	*/
    virtual void drawValue(QPainter &p, const QRect& pieRect,
                               const QModelIndex &index, double value,
                               double angle1, double angle2,
                               bool isHighlighted);

	virtual void drawCutout(QPainter &p, const QRect &cutRect);

protected:
    bool m_showNegatives = false;
    int m_margin = 3;

    float m_cutout = 0;
	QWidget *m_centralWidget = nullptr;

	struct HoverData {
		double angleHl1 = 0.0, angleHl2 = 0.0, valueHl = 0.0;
		QRect segmentRect;
	} hoverData;
};


}

#endif // RINGPLOTBASE_H
