#ifndef KMACDGRID_H
#define KMACDGRID_H

#include "stockgrid.h"

class KMacdGrid : public StockGrid
{
public:
    explicit KMacdGrid(QWidget* parent = 0);
    void virtual initial();
    void virtual drawLine();
    void virtual drawYtick();
    void virtual paintEvent(QPaintEvent* event);
    void virtual keyPressEvent(QKeyEvent* event);
    void virtual calAtomGridHeight();
    void virtual resizeEvent(QResizeEvent *event);

    //画macd方块
    void drawBar();

    //画DIF DEA
    void drawDifDea();

    //获取画macd线的指标
    void virtual getSelfIndicator();

    //画MACD的具体信息- MACD、DIFF、DEA
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

    double highestMacd;
    double lowestMacd;
    int lineWidth;
};

#endif // KMACDGRID_H
