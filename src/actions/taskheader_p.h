#ifndef TASKHEADER_P_H
#define TASKHEADER_P_H

#include "actionpanelscheme.h"
#include "actionlabel.h"

#include <QLabel>


namespace QSint
{


class TaskHeader : public QFrame
{
  Q_OBJECT

  typedef QFrame BaseClass;

  friend class ActionGroup;

public:
  TaskHeader(const QIcon &icon, const QString &title, bool expandable, QWidget *parent = 0);

  inline bool expandable() const { return myExpandable; }
  void setExpandable(bool expandable);

  void setScheme(ActionPanelScheme *scheme);

signals:
  void activated();

public slots:
  void fold();

protected slots:
  void animate();

protected:
  virtual void paintEvent ( QPaintEvent * event );
  virtual void enterEvent ( QEvent * event );
  virtual void leaveEvent ( QEvent * event );
  virtual void mouseReleaseEvent ( QMouseEvent * event );
  virtual void keyPressEvent ( QKeyEvent * event );
  virtual void keyReleaseEvent ( QKeyEvent * event );

  bool eventFilter(QObject *obj, QEvent *event);

  void changeIcons();

  ActionPanelScheme *myScheme;

  bool myExpandable;
  bool m_over, m_buttonOver, m_fold;
  double m_opacity;

  ActionLabel *myTitle;
  QLabel *myButton;
};


}

#endif // TASKHEADER_P_H
