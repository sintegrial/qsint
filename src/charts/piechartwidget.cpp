#include <qmath.h>

#include "piechartwidget.h"


namespace QSint
{


PieChartWidget::PieChartWidget(QWidget *parent) :
    PieChart(parent)
{
	m_model.setColumnCount(1);
	setModel(&m_model);
}


void PieChartWidget::clear()
{
    m_model.clear();
	m_model.setColumnCount(1);
}


int PieChartWidget::addData(const QString &text, const QBrush &brush, double value)
{
    QStandardItem *item = new QStandardItem;
    item->setData(value, Qt::EditRole);
    item->setBackground(brush);

	int r = m_model.rowCount();
    m_model.appendRow(item);

	if (!text.isEmpty())
		m_model.setHeaderData(r, Qt::Vertical, text);

    return r;
}


bool PieChartWidget::removeData(int index)
{
    if (index >= 0 && index < m_model.rowCount())
    {
        m_model.removeRow(index);
        return true;
    }

    return false;
}


}
