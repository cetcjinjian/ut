#ifndef KDAYGRID_H
#define KDAYGRID_H



#include <QDockWidget>



#include "kLineGrid.h"
#include "kVolumeGrid.h"
#include "kMacdGrid.h"
#include "Subscribe.h"
#include "DataFile.h"

#include <QMessageBox>

class KLineGrid;
class KVolumeGrid;
class KMacdGrid;
class Subscribe;
class DataFile;
class queryCode;

class kDayGrid : public QWidget
{
public:
    explicit kDayGrid(QWidget* parent);
    void virtual keyPressEvent(QKeyEvent* event);
	void virtual mouseMoveEvent(QMouseEvent* event);

    QString getCodeStr() const;
    void setCodeStr(const QString &value);
    void showNewKline();

public:
    KLineGrid* pLine= nullptr;
    KVolumeGrid* pVolume= nullptr;
    KMacdGrid* pMacd= nullptr;
    Subscribe* mSubscribe= nullptr;
    DataFile* pData= nullptr;    
    QString codeStr;

};



#endif // KDAYGRID_H
