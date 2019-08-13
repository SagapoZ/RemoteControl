#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QPoint>
#include <QPixmap>
#include <QTcpSocket>
#include <QByteArray>

class MyThread:public QThread
{
    Q_OBJECT

public:
    explicit MyThread(QObject *parent = nullptr);
    QTcpSocket msocket;
    void fetchPicturesSlot();

protected:
    void run();

private slots:
    void ReadMessage();

signals:
    void showImag(QImage);

private:
    QPixmap pixmap;
    QByteArray imageData;
    int datasize;
};

#endif // MYTHREAD_H
