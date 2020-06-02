#ifndef PIECHARTWIDGET_H
#define PIECHARTWIDGET_H


#include "piechart.h"

#include <QStandardItemModel>


namespace QSint
{


/**
    \brief Class representing a piechart widget with own data model.
    \since 0.4

    \image html PieChart.png An example of PieChart

    Unlike PieChart, PieChartWidget allows to build pie chart diagrams using simpler API.
*/
class PieChartWidget : public PieChart
{
    Q_OBJECT

public:
    PieChartWidget(QWidget *parent = 0);

    /// Returns amount of data entries in the diagram.
    int dataCount() const    { return m_model.rowCount(); }

public Q_SLOTS:
    /// Appends new data entry to the diagram. Returns index of the data entry.
    int addData(const QString &text, const QBrush &brush, double value);

    /// Removes data entry at \a index. Returns \a true if \a index is valid and data has been removed.
    bool removeData(int index);

    /// Removes all the data entries.
    void clear();

protected:

protected:
    QStandardItemModel m_model;
};


}


#endif
