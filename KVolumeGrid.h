#ifndef KVOLUMEGRID_H
#define KVOLUMEGRID_H

#include "stockgrid.h"



class KVolumeGrid : public StockGrid
{
public:
    explicit KVolumeGrid(QWidget* parent = 0);
    void virtual initial();
    void virtual drawLine();
    void virtual drawYtick();
    void virtual paintEvent(QPaintEvent* event);
    void virtual keyPressEvent(QKeyEvent* event);

    //画成交量的方柱
    void drawKVolume();

    //画均线
    void drawAverageLine(int day);

    //画成交量的具体信息- 总手、5日均值、10日均值
    void drawInformation();


    //获取画成交量的指标-最大成交量 最小成交量
    void virtual getSelfIndicator();

    //键盘没按下，鼠标移动时显示
    void virtual drawCrossLine(double begin = 0 , double end = 0);
    void virtual drawCorssVerLine();
    void virtual drawCorssHorLine();
    void virtual drawTips(double begin = 0 , double end = 0);

   // void virtual keyPressEvent(QKeyEvent *event);


    //键盘按下时显示
    void virtual drawCrossLineKeyDown(double begin = 0 , double end = 0);
    void virtual drawCorssVerLineKeyDown();
    void virtual drawCorssHorLineKeyDown(double start , double end,int types = 0);
    void virtual drawTipsKeyDown(double begin = 0 , double end = 0,int types = 0);




private:
    double maxVolume;
    int lineWidth;    
};

#endif // KVOLUMEGRID_H
