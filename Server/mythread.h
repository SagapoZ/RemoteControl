#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QPixmap>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QClipboard>
#include <QContextMenuEvent>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

class MyThread:public QThread
{
    Q_OBJECT

public:
    explicit MyThread(QTcpSocket* socket,QObject *parent = nullptr);
    void shotScreenSlot();
    ~MyThread();
protected:
    void run();

private:
   QTcpSocket* msocket;
   QPixmap pixmap;
};

#endif // MYTHREAD_H
