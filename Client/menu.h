#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include "client.h"
#include <QUdpSocket>
#include <QJsonObject>


namespace Ui {
class Menu;
}

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();
    static QString ip;
    static QString port;

    void sendMsg();
    void rcevMsg();

    QJsonObject JsonParse(QByteArray array);

private slots:
    void on_DesktopBt_clicked();
    void on_pushButton_clicked();
    void on_actionback_triggered();
    void on_imagBt_clicked();

private:
    Ui::Menu *ui;
    Client *w;
    bool flag;
    QUdpSocket udpsocket;
};

#endif // MENU_H
