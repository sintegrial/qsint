#include "dial.h"

#include <QPainter>
#include <QVariant>
#include <QMouseEvent>


namespace QSint
{


Dial::Dial(QWidget *parent) : QDial(parent)
{
	connect(this, &QDial::valueChanged, this, &Dial::updateLabel);

	updateLabel();

	update();
}


void Dial::setValue(int v)
{
	QDial::setValue(v);

	update();
}


void Dial::setSuffixText(const QString &suffix)
{
	m_suffix = suffix;

	update();
}


void Dial::setLabelText(const QString &text)
{
	m_text = text;

	update();
}


void Dial::paintEvent(QPaintEvent *pe)
{
	QDial::paintEvent(pe);

	updateLabel();

	QPainter p(this);

	p.drawText(rect(), Qt::AlignCenter, m_valueText);
}


void Dial::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::RightButton)
	{
		Q_EMIT rightClicked();
	}
}


void Dial::updateLabel()
{
	if (m_text.size())
	{
		m_valueText = m_text;
		update();
		return;
	}

	m_valueText = QString::number(value());

	if (m_suffix.size())
	{
		m_valueText += m_suffix;
	}
	else
	{
		QString suffix = property("Suffix").toString();
		if (suffix.size())
			m_valueText += suffix;
	}
}


}