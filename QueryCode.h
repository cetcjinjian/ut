#ifndef QUERYCODE_H
#define QUERYCODE_H

#include <QDialog>

#include "mainwindow.h"

class MainWindow;

namespace Ui {
class QueryCode;
}

class QueryCode : public QDialog
{
    Q_OBJECT

public:
    explicit QueryCode(QWidget *parent = 0);

    ~QueryCode();

private slots:
    void on_pushButton_clicked();

private:
    Ui::QueryCode *ui;   

signals:
	
};

#endif // QUERYCODE_H
