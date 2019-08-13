#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QTimer>
#include <QClipboard>
#include <QPixmap>
#include <QTcpSocket>
#include <QByteArray>
#include "mythread.h"
#include <QDesktopWidget>
#include <QMouseEvent>

namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();
     MyThread *th;

    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);
    void sendData(QByteArray eventArr);

private slots:
    void ShowImage(QImage img);
    void on_actionback_triggered();

private:
    Ui::Client *ui;
    QDesktopWidget *d;
    QPoint curPoint;
};

#endif // CLIENT_H
