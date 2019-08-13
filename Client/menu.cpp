#include "menu.h"
#include "ui_menu.h"
#include <QByteArray>
#include "controldata.h"
#include <QDebug>
#include <QDateTime>
#include <QJsonParseError>
#include <QJsonDocument>
#include "sendfile.h"

Menu::Menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    //进来绑定udp可以开始发送信息

    udpsocket.bind(8080);

    flag = false;
    //关联读数据信号
    connect(&udpsocket, &QUdpSocket::readyRead, this, &Menu::rcevMsg);
}
QString Menu::ip=nullptr;
QString Menu::port=nullptr;

Menu::~Menu()
{
    delete ui;
}

void Menu::on_pushButton_clicked()
{
    sendMsg();
    qDebug()<<"senMsg";
}

void Menu::sendMsg()
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("hh:mm:ss"); //设置显示格式

    QString msg = str+" : "+this->ui->msgEdit->text();
    qDebug()<<"Msg"<<msg;
    QByteArray msgArr = ControlData::msgData(msg,SEND_MSG);

    w->th->msocket.write(msgArr);
}

void Menu::rcevMsg()
{
    //接收udp数据
    QByteArray baRecv;
    while(udpsocket.hasPendingDatagrams())
    {
        baRecv.resize(udpsocket.pendingDatagramSize());
        udpsocket.readDatagram(baRecv.data(),baRecv.size());
        QString strRecvData = baRecv;
        ui->rcvBrowser->append(strRecvData);
    }
}

void Menu::on_DesktopBt_clicked()
{
    ip = ui->ipEdit->text();
    port = ui->portEdit->text();
    if(!flag)
    {
        //创建显示界面
        w = new Client(this);
        flag=true;
    }

    //远程控制界面
    w->show();
    //隐藏主界面
    this->hide();
}

QJsonObject Menu::JsonParse(QByteArray array)
{
    //解析Json
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(array, &error);
    if(error.error != QJsonParseError::NoError)//校验格式是否有错
    {
        qDebug()<<"json error";

    }
    QJsonObject obj = doc.object();
    return obj;
}

void Menu::on_actionback_triggered()
{
    this->close();
}

void Menu::on_imagBt_clicked()
{

    //进入灯光控制界面
   SendFile *w = new SendFile(this);
   w->show();
   //隐藏主界面
   this->hide();


}









