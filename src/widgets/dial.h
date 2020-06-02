#pragma once

#include <QtGui/QFont>
#include <QtWidgets/QDial>


namespace QSint
{


/**
\brief Extended QDial widget with additional value label in the middle.
\since 0.4

\image html Dial.png An example of Dial widget
*/
class Dial : public QDial
{
	Q_OBJECT

public:
	Dial(QWidget *parent = nullptr);

	void setLabelText(const QString &text);
	void setSuffixText(const QString &suffix);
	
	virtual void setValue(int v);

Q_SIGNALS:
	void rightClicked();

protected:
	virtual void paintEvent(QPaintEvent *pe);
	virtual void mousePressEvent(QMouseEvent *e);

private Q_SLOTS:
	void updateLabel();

private:
	QString m_text;
	QString m_valueText;
	QString m_suffix;
};


}
