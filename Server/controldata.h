#ifndef CONTROLDATA_H
#define CONTROLDATA_H

#include <QApplication>
#include <QPoint>

#define MOUSE_MOVE_TO          1
#define MOUSE_LEFT             2
#define MOUSE_RIGHT            3
#define MOUSE_WHEEL            4
#define MOUSE_DOUBLE_CLICK     5
#define RCEV_MSG               6
#define SEND_MSG               7

class ControlData
{
public:
    ControlData();
    //打包数据
    static QByteArray controlData(QDesktopWidget *d, double x, double y, int event);

    static QByteArray msgData(QString msg,int event);
};

#endif // CONTROLDATA_H
