#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTimer>
#include <QPixmap>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QTcpServer>
#include <QTcpSocket>
#include "mythread.h"
#include "mythread.h"
#include <QHostAddress>
#include <QPixmap>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QClipboard>
#include <QContextMenuEvent>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QUdpSocket>
#include "controldata.h"

namespace Ui {
class Server;
}

class Server : public QMainWindow
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);
    ~Server();

    QJsonObject JsonParse(QByteArray array);
    void selecEvent();

    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    void showPicture(QImage img);
private slots:
    void on_connBt_clicked();
    void on_stopBt_clicked();
    void new_client();
    void reciveData();
    void on_closeBt_clicked();
    void on_sendmsgBt_clicked();
    void rcvFile();
    void on_minBt_clicked();
    void on_maxBt_clicked();

    void on_pushButton_clicked();

private:
    Ui::Server *ui;
    MyThread *th;
    QTcpServer mserver;
    QTcpSocket *msocket;
    QUdpSocket *udpsocket;
    QByteArray eventArr;
    QHostAddress ip;
    int pc_x;
    int pc_y;
    QPoint z;
    QByteArray picBuffer;
    int datasize;
};

#endif // SERVER_H
