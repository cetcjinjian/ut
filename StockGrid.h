#ifndef STOCKGRID_H
#define STOCKGRID_H

#include "AutoGrid.h"

#include "subscribe.h"


class Subscribe;

class AutoGrid;
class QWidget;
class DataFile;
class QPoint;


class StockGrid : public AutoGrid
{
public:
    explicit StockGrid(QWidget* parent = 0);
    void virtual paintEvent(QPaintEvent* event);


    void virtual keyPressEvent(QKeyEvent* event);
    void virtual mouseMoveEvent(QMouseEvent* event);
    void virtual mousePressEvent(QMouseEvent* event);


    void virtual keyPressEvent2(QKeyEvent* event);
    void virtual mouseMoveEvent2(QMouseEvent* event);
    void virtual mousePressEvent2(QMouseEvent* event);



    void virtual resizeEvent(QResizeEvent* event);
    void virtual initial();
    void virtual drawLine();

    //分别画x轴和y轴坐标
    void virtual drawXtick();
    void virtual drawYtick(double begin , double end);

    //每个继承的子类分别获取自己所需的参数
    void virtual getSelfIndicator();


    //键盘没按下，鼠标移动时显示
    void virtual drawCrossLine(double begin = 0 , double end = 0);
    void virtual drawCorssVerLine();
    void virtual drawCorssHorLine();
    void virtual drawTips(double begin = 0 , double end = 0);



    //键盘按下时显示
    void virtual drawCrossLineKeyDown(double begin = 0 , double end = 0);
    void virtual drawCorssVerLineKeyDown();
    void virtual drawCorssHorLineKeyDown(double start = 0 , double end =0 , int types = 0);
    void virtual drawTipsKeyDown(double begin = 0 , double end = 0 ,int types = 0);


    void setData(DataFile* pData);

    ~StockGrid();



    int getStartIndex() const;
    void setStartIndex(int value);

    int getEndIndex() const;
    void setEndIndex(int value);

    int getCurrentIndex() const;
    void setCurrentIndex(int value);

    int getTotalIndex() const;
    void setTotalIndex(int value);

    int getLineWidth() const;
    void setLineWidth(int value);

    double getXScale() const;
    void setXScale(double value);

    double getYScale() const;
    void setYScale(double value);

    QPoint getMousePoint() const;
    void setMousePoint(const QPoint &value);

    DataFile *getPData() const;
    void setPData(DataFile *value);
    void setSubscribe(Subscribe* pSubscribe);

private:
    DataFile* pData = nullptr;

    //画线的起始位置，终止位置，总长与当前位置。
    int startIndex;
    int endIndex;
    int currentIndex;
    int totalIndex;

    //画笔线宽 - 间隔
    int lineWidth;

    //键盘是否按下
    bool isKeyDown = false;

    //鼠标位置
    QPoint mousePoint;

    //是否显示十字线
    bool bCross = false;

    //订阅者
    Subscribe* pSubscribe;

};

#endif // STOCKGRID_H
