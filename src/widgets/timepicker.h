#ifndef TIMEPICKER_H
#define TIMEPICKER_H

#include <QWidget>
#include <QTime>
#include <QButtonGroup>


namespace QSint
{


class TimePicker : public QWidget
{
    Q_OBJECT

public:
    /** Constructor.
      */
	explicit TimePicker(QWidget *parent = 0);

	/** Returns current time.
	*/
	QTime time() const
		{ return m_time; }

	/** Sets current time.
	*/
	void setTime(const QTime& time);

Q_SIGNALS:
	void timePicked(const QTime& time);

private Q_SLOTS:
	void hourClicked(int hour);
	void minuteClicked(int minute);

protected:
	QTime m_time;
	QButtonGroup m_hourButtons;
	QButtonGroup m_minuteButtons;
};


}


#endif // TIMEPICKER_H
