#include "SubScribe.h"
#include "KDayGrid.h"
#include <QWidget>

Subscribe::Subscribe(QWidget* parent): QWidget(parent)
{
    ;
}

void Subscribe::Attach(StockGrid* grid)
{
    list.push_back(grid);
}

void Subscribe::Notify_keyPressEvent(QKeyEvent* event)
{
    foreach (StockGrid* var, list) {
        var->keyPressEvent2(event);
    }
    kDayGrid* pDayGrid = dynamic_cast<kDayGrid*>(this->parent());
    pDayGrid->keyPressEvent(event);

}

void Subscribe::Notify_mouseMoveEvent(QMouseEvent* event)
{
    foreach (StockGrid* var, list) {
        var->mouseMoveEvent2(event);
    }
}

void Subscribe::Notify_mousePressEvent(QMouseEvent* event)
{
    foreach (StockGrid* var, list) {
        var->mousePressEvent2(event);
    }
}
