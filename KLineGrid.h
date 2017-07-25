#ifndef KLINEGRID_H
#define KLINEGRID_H

#include "StockGrid.h"
#include "KLineDetail.h"


class ShowDetail;

class KLineGrid : public StockGrid
{
public:
    explicit KLineGrid(QWidget* parent = 0);
    void virtual initial();
    void virtual drawLine();
    void virtual drawYtick();
    void virtual paintEvent(QPaintEvent* event);
    void virtual keyPressEvent(QKeyEvent* event);

    //画k线
    void drawKLine();

    //画均线
    void drawAverageLine(int day);

    //获取画k线的指标-最大价格 最小价格
    void virtual getSelfIndicator();

    //画日k的具体信息- 股票名称、MA5、MA10、MA20、MA30、MA60
    void drawInformation();

    //键盘没按下，鼠标移动时显示
    void virtual drawCrossLine(double begin = 0 , double end = 0);
    void virtual drawCorssVerLine();
    void virtual drawCorssHorLine();
    void virtual drawTips(double begin = 0 , double end = 0);

    //键盘按下时显示
    void virtual drawCrossLineKeyDown(double begin = 0 , double end = 0);
    void virtual drawCorssVerLineKeyDown();
    void virtual drawCorssHorLineKeyDown(double start , double end,int types = 0);
    void virtual drawTipsKeyDown(double begin = 0 , double end = 0,int types = 0);



private:

    double highestBid;
    double lowestBid;
    int lineWidth;

	KLineDetail* pdetail = nullptr;

public:
	QString stockName = u8"上海科技";
};

#endif // KLINEGRID_H
