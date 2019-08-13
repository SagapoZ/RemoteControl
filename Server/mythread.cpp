#include "mythread.h"
#include <QApplication>
#include <QBuffer>
#include <QHostAddress>
#include <QAbstractSocket>


MyThread::MyThread(QTcpSocket* socket,QObject *parent):QThread (parent)
{
    msocket = socket;
}

void MyThread:: run()
{
    qDebug()<<"run"<<endl;
    while (1) {
        shotScreenSlot();
        msleep(200);
    }
}

void MyThread::shotScreenSlot()
{
    //截图
    this->pixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
    //将图片转化为字节流
    QBuffer buffer;
    buffer.open(QIODevice::ReadWrite);

    this->pixmap.save(&buffer,"jpg");

    quint32 pix_len = (quint32)buffer.data().size();
    qDebug("image size:%d",pix_len);

    QByteArray dataArray;
    //绑定数据流
    QDataStream out(&dataArray,QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_4_6);
    out<<pix_len;
    dataArray.append(buffer.data());

    //发送dataArra
    msocket->write(dataArray);
    msocket->flush();

    //清空
    dataArray.resize(0);
    buffer.reset();
}

MyThread::~MyThread()
{
    msocket->close();
    delete msocket;
}

