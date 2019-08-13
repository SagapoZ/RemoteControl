#include "client.h"
#include "ui_client.h"
#include <QHostAddress>
#include <QMessageBox>
#include <QBuffer>
#include <QImageReader>
#include <QImage>
#include "menu.h"
#include <QPoint>
#include <QMouseEvent>
#include <QPixmap>
#include <QDesktopWidget>
#include "controldata.h"

static bool isMove=false;

Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    showFullScreen();

    //初始化线程
    th = new MyThread();
    th->start();

    connect(th,&MyThread::showImag,this,&Client::ShowImage);
}

void Client::ShowImage(QImage img)
{
    ui->playerLabel->setScaledContents(true);
    QPixmap pix = QPixmap::fromImage(img);
    ui->playerLabel->setPixmap(pix.scaled(ui->playerLabel->size(),
                                          Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation));
}

void Client::mouseMoveEvent(QMouseEvent *e)
{

    QRect screenrect;
    QDesktopWidget* desktopWidget = QApplication::desktop();//获取分辨率
    screenrect = desktopWidget->screenGeometry();

    QPoint point;
    point=e->pos();
    if( (point-curPoint).manhattanLength() != 0)//获取当前点击的坐标
    {
        isMove = true;
        //执行拖动效果
        double Xpercent=(double)point.x()/screenrect.width();//算出百分百比
        double Ypercent=(double)point.y()/screenrect.height();
        QByteArray eventArr =  ControlData::controlData(d,Xpercent,Ypercent,MOUSE_MOVE_TO);
        sendData(eventArr);
    }
}

void Client::mouseReleaseEvent(QMouseEvent *e)
{
    isMove = false;
}

void Client::mouseDoubleClickEvent(QMouseEvent *e)
{
    //双击事件发生
    QRect screenrect;
    screenrect = ui->playerLabel->geometry();

    QPoint point;
    point=e->pos();//获取当前点击的坐标

    double Xpercent=(double)point.x()/screenrect.width();//算出百分百比
    double Ypercent=(double)point.y()/screenrect.height();
    QByteArray eventArr =  ControlData::controlData(d,Xpercent,Ypercent,MOUSE_DOUBLE_CLICK);
    sendData(eventArr);
}

//鼠标按压加左击
void Client::mousePressEvent(QMouseEvent *e)
{
    curPoint = e->pos();
    if(!isMove)
    {
        QRect screenrect;
        screenrect = ui->playerLabel->geometry();

        QPoint point;
        point=e->pos();//获取当前点击的坐标

        double Xpercent=(double)point.x()/screenrect.width();//算出百分百比
        double Ypercent=(double)point.y()/screenrect.height();
        QByteArray eventArr =  ControlData::controlData(d,Xpercent,Ypercent,MOUSE_LEFT);
        sendData(eventArr);
    }

}

void Client::sendData(QByteArray eventArr)
{
    //tcp发送数据
    th->msocket.write(eventArr);
}

void Client::on_actionback_triggered()
{
    //返回到主界面
    this->parentWidget()->show();
    this->hide();
}

Client::~Client()
{
    delete ui;
}













