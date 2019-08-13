#include "controldata.h"
#include <QJsonObject>
#include <QDesktopWidget>
#include <QJsonDocument>

ControlData::ControlData()
{

}
QByteArray ControlData::msgData(QString msg,int event)
{
    QJsonObject json;

    //鼠标点击的坐标SEND_MSG
    json.insert("event", event);
    json.insert("Msg", msg);

    // 构建 JSON 文档
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    return byteArray;
}
QByteArray ControlData::controlData(QDesktopWidget *d, double x, double y,int event)
{
    QJsonObject json;

    //鼠标点击的坐标
    json.insert("PointX", x);
    json.insert("PointY", y);

    //鼠标事件
    json.insert("event",event);


    // 构建 JSON 文档
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    return byteArray;
}

