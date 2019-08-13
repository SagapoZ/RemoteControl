#include "server.h"
#include "ui_server.h"
#include <QMenu>
#include <QAction>
#include <QCursor>
#include <QBuffer>
#include <QJsonParseError>
#include <QJsonObject>
#include <windows.h>
#include <QDateTime>
#include <QFileDialog>
#include <QImageReader>
#include "htmlui.h"

Server::Server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    //设置无边框
    setWindowFlags(Qt::FramelessWindowHint);
    udpsocket = new QUdpSocket(this);
    mserver.setParent(this);
    //关联客户端连接信号
    connect(&mserver, &QTcpServer::newConnection, this, &Server::new_client);
    datasize = 0;
}

void Server::on_connBt_clicked()
{
    //开启服务器
    mserver.listen(QHostAddress::Any,8080);
    //绑定udp
    udpsocket->bind(8080);
    connect(udpsocket,&QUdpSocket::readyRead,this,&Server::rcvFile);
}

void Server::on_stopBt_clicked()
{
    //线程停止
    th->terminate();
}

void Server::new_client()
{
    //创建与客户端通信的套接字
    msocket = mserver.nextPendingConnection();
    connect(msocket,&QTcpSocket::readyRead,this,&Server::reciveData);
    ip =  msocket->peerAddress();
    ui->ipBrowser->append(ip.toString().remove("::ffff:"));
    th = new MyThread(msocket);
    //启动线程
    th->start();
}

void Server::rcvFile()
{
    //接收udp数据
    QByteArray baRecv;
    QString httpUrl;
    while(udpsocket->hasPendingDatagrams())
    {
        baRecv.resize(udpsocket->pendingDatagramSize());
        udpsocket->readDatagram(baRecv.data(),baRecv.size());
        QString strRecvData = baRecv;
        httpUrl = strRecvData;
        ui->msgBrowser->append(strRecvData);
    }
}

void Server::on_sendmsgBt_clicked()
{
   //发送消息
   QString msg = ui->sendEdit->toPlainText();
   //发送信息
   QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
   QString str = time.toString("hh:mm:ss"); //设置显示格式
   QString msgArr = str+":"+msg;
   udpsocket->writeDatagram(msgArr.toUtf8(),ip, 8080);
   //QByteArray data = ControlData::msgData(msgArr, SEND_MSG);
   ui->msgBrowser->append(msg);

}

void Server::reciveData()
{
    //接收客户端发过来的任务
    eventArr = msocket->readAll();
    QString strJson(eventArr);
    ui->ipBrowser->append(strJson);
    selecEvent();
}

void Server::selecEvent()
{
    QRect screenrect;
    QDesktopWidget* desktopWidget = QApplication::desktop();//获取分辨率
    screenrect = desktopWidget->screenGeometry();

    //得到Json对象
    QJsonObject eventobj = JsonParse(eventArr);
    //判断事件
    int e = eventobj.value("event").toInt();
    if(e == RCEV_MSG)
    {
        ui->msgBrowser->append(eventobj.value("Msg").toString());
        ui->ipBrowser->append("RCEV_MSG");
    }
    else {
        double percentX = eventobj.value("PointX").toDouble();
        double percentY = eventobj.value("PointY").toDouble();

        pc_x = percentX*screenrect.width();
        pc_y = percentY*screenrect.height();

        switch (e)
        {
            case MOUSE_MOVE_TO:
               mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_MOVE,
                           pc_x*65532/screenrect.width(),
                           pc_y*65532/screenrect.height(), 0, 0);
               ui->ipBrowser->append("MOUSE_MOVE_TO");

            break;

            case MOUSE_LEFT:
                mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE,
                        pc_x*65532/screenrect.width(),
                        pc_y*65532/screenrect.height(), 0, 0);
                mouse_event( MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP,0,0, 0, 0);
                ui->ipBrowser->append("MOUSE_LEFT");
            break;

            case MOUSE_DOUBLE_CLICK:
                mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE,
                        pc_x*65532/screenrect.width(),
                        pc_y*65532/screenrect.height(), 0, 0);
                mouse_event( MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP,0,0, 0, 0);
                mouse_event( MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP,0,0, 0, 0);
                ui->ipBrowser->append("MOUSE_DOUBLE_CLICK");
            break;

            default:
                break;
        }
    }
}

QJsonObject Server::JsonParse(QByteArray array)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(array, &error);
    if(error.error != QJsonParseError::NoError)//校验格式是否有错
    {
        qDebug()<<"json error";

    }
    QJsonObject obj = doc.object();
    return obj;
}

Server::~Server()
{
    delete ui;
}


void Server::on_closeBt_clicked()
{
    this->close();
}

void Server::mouseMoveEvent(QMouseEvent *e)
{
    QWidget::mouseMoveEvent(e);

    //一直获取鼠标的位置
    QPoint y = e->globalPos();
    //一直获取窗口的位置
    QPoint x = y - this->z;
    this->move(x);
}

void Server::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
    QPoint y = e->globalPos(); //鼠标相对于桌面左上角的位置
    //存储
    QPoint x = this->geometry().topLeft(); //窗口相对于桌面左上角的位置
    this->z = y - x;   //鼠标相对于窗口左上角的位置，定值
}


void Server::mouseReleaseEvent(QMouseEvent *e)
{
    QWidget::mouseReleaseEvent(e);
    this->z = QPoint();
}

void Server::on_minBt_clicked()
{
    //最小化
    setWindowState(Qt::WindowMinimized);
}

void Server::on_maxBt_clicked()
{
    setWindowState(Qt::WindowMaximized);
}

void Server::on_pushButton_clicked()
{
    HtmlUI *w = new HtmlUI(this);
    w->show();
    this->hide();
}
