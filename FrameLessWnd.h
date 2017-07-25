#ifndef FRAMELESSWND
#define FRAMELESSWND


#include <qwidget.h>
#include <QMouseEvent>


enum CursorPos { Default, Right, Left, Bottom, Top, TopRight, TopLeft, BottomRight, BottomLeft };
struct pressWindowsState
{
	bool    MousePressed;
	bool   IsPressBorder;
	QPoint  MousePos;
	QPoint  WindowPos;
	QSize PressedSize;
};



class FrameLessWnd : public QWidget
{
	Q_OBJECT
public:
	FrameLessWnd(QWidget *parent = 0);
	~FrameLessWnd();
	inline void setBorder(int border);
	void mouseMoveRect(const QPoint &p);
protected:
	virtual void mouseMoveEvent(QMouseEvent *event); //交给别个调用
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	pressWindowsState m_state;
	int m_border;
	CursorPos m_curPos;
};


#endif // !FRAMELESSWND
