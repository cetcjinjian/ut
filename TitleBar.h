#ifndef TITLE_BAR
#define TITLE_BAR

#include <QWidget>


class QLabel;
class QPushButton;
class QMenu;
class QMenuBar;

class TitleBar : public QWidget
{
	Q_OBJECT

public:
	explicit TitleBar(QWidget *parent = 0);
	~TitleBar();

protected:

	// 双击标题栏进行界面的最大化/还原
	virtual void mouseDoubleClickEvent(QMouseEvent *event);

	// 进行鼠界面的拖动
	virtual void mousePressEvent(QMouseEvent *event);

	// 设置界面标题与图标
	virtual bool eventFilter(QObject *obj, QEvent *event);

	private slots:

	// 进行最小化、最大化/还原、关闭操作
	void onClicked();

private:

	// 最大化/还原
	void updateMaximize();

private:
	QLabel *m_pIconLabel;
	QLabel *m_pTitleLabel;
	QPushButton *m_pMinimizeButton;
	QPushButton *m_pMaximizeButton;
	QPushButton *m_pCloseButton;


	QMenuBar* m_pMenuBar;
	QMenu* m_pSystemMenu;
	QMenu* m_pBidMenu;
	QMenu* m_pAnalyzeMenu;
	QMenu* m_pMarketMenu;
	QMenu* m_pEntrustMenu;
	QMenu* m_pSmartMenu;
	QMenu* m_pToolMenu;
	QMenu* m_pInformationMenu;
	QMenu* m_pHelpMenu;

};

#endif // TITLE_BAR