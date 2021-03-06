﻿#ifndef AUTOGRID_H
#define AUTOGRID_H

#include "FrameLessWnd.h"


class AutoGrid : public FrameLessWnd
{
    Q_OBJECT
public:
    explicit AutoGrid(QWidget *parent = 0);

    void virtual initial();
    void virtual drawBK();
    void virtual resizeEvent(QResizeEvent* event);
    void virtual calAtomGridHeight();
    void virtual calAtomGridWidth();
    void virtual paintEvent(QPaintEvent* event);    
    void virtual drawGrid();
    void virtual drawHorLine();
    void virtual drawVerLine();


    int getMarginLeft() const;
    void setMarginLeft(int value);

    int getMarginRight() const;
    void setMarginRight(int value);

    int getMarginTop() const;
    void setMarginTop(int value);

    int getMarginBottom() const;
    void setMarginBottom(int value);

    int getWidgetHeight() const;

    int getWidgetWidth() const;

    double getGridHeight() const;

    double getGridWidth() const;

    int getHGridNum() const;
    void setHGridNum(int value);

    int getWGridNum() const;
    void setWGridNum(int value);

    double getAtomGridHeightMin() const;
    void setAtomGridHeightMin(double value);

    double getAtomGridWidthMin() const;
    void setAtomGridWidthMin(double value);

    double getAtomGridHeight() const;


    double getAtomGridWidth() const;

    void setAtomGridHeight(double value);

    void setAtomGridWidth(double value);

private:


    //表格距边框距离
    int marginLeft      = 40;
    int marginRight     = 40;
    int marginTop       = 20;
    int marginBottom    = 5;

    //当前widget的宽度和高度
    int widgetHeight;
    int widgetWidth;

    //当前表格的宽度和高度
    double gridHeight;
    double gridWidth;

    //当前表格中最小表格的宽度和高度
    double atomGridHeight;
    double atomGridWidth;

    //表格中小格子的数量
    int hGridNum;
    int wGridNum;

    //当前表格中最小表格的宽度和高度的最小值
    double atomGridHeightMin;
    double atomGridWidthMin;


signals:

public slots:
};

#endif // AUTOGRID_H
