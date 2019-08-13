#include "mythread.h"
#include "menu.h"
#include <QHostAddress>
#include <QBuffer>
#include <QImageReader>

MyThread::MyThread(QObject *parent):QThread (parent)
{
    //发送数据
    datasize=0;
    //连接服务器
   msocket.connectToHost(QHostAddress(Menu::ip),
                           Menu::port.toUShort()); // 连接到服务器
   //msocket.connectToHost(QHostAddress("192.168.43.56"),8080);
    // 信号和槽的连接
    connect(&msocket, SIGNAL(readyRead()), this, SLOT(ReadMessage()));
}

void MyThread::run()
{
    QThread::run();
}

void MyThread::ReadMessage()
{
    fetchPicturesSlot();
}

void MyThread::fetchPicturesSlot()
{
    //第一次读
    if(datasize == 0)
    {
        QDataStream in(&msocket);
        in.setVersion( QDataStream::Qt_4_6);
        if(msocket.bytesAvailable() < sizeof(quint32))
        {
            return;
        }
        in>>datasize;
    }
    //然后根据图片大小信息接收JPG格式图片
    if(datasize > msocket.bytesAvailable())
    {
        return;
    }
    //显示图片
    QByteArray Data =msocket.read(datasize);

    QBuffer buffer(&Data);

    buffer.open(QIODevice::ReadOnly);
    QImageReader reader(&buffer,"jpg");
    QImage img = reader.read();
    if(!img.isNull())
    {
        //发送显示图片信号
        emit showImag(img);
    }
    datasize = 0;
 }
