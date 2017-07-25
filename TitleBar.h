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

	// ˫�����������н�������/��ԭ
	virtual void mouseDoubleClickEvent(QMouseEvent *event);

	// �����������϶�
	virtual void mousePressEvent(QMouseEvent *event);

	// ���ý��������ͼ��
	virtual bool eventFilter(QObject *obj, QEvent *event);

	private slots:

	// ������С�������/��ԭ���رղ���
	void onClicked();

private:

	// ���/��ԭ
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