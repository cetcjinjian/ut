#ifndef SUBSCRIBE_H
#define SUBSCRIBE_H



#include <QVector>
#include "StockGrid.h"


class StockGrid;


class Subscribe : public QWidget
{
public:
    explicit Subscribe(QWidget* parent);
    void Attach(StockGrid* grid);
    void Notify_keyPressEvent(QKeyEvent* event);
    void Notify_mouseMoveEvent(QMouseEvent* event);
    void Notify_mousePressEvent(QMouseEvent* event);
private:

    QVector<StockGrid*> list;
};

#endif // SUBSCRIBE_H
