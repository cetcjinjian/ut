#ifndef REALTIMETRADE_H
#define REALTIMETRADE_H

#include "FrameLessWnd.h"
#include <QTableWidget>


class RealTimeTrade : public QWidget
{
    Q_OBJECT
public:
    explicit RealTimeTrade(QWidget *parent = 0);



private:
    QTableWidget* pTradeTable;


signals:

public slots:
};

#endif // REALTIMETRADE_H
