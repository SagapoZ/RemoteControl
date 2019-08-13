#include "hdbutton.h"
#include <QApplication>
#include <QDebug>
#include <QKeyEvent>

HDButton::HDButton(QWidget *parent):QPushButton(parent)
{

}

HDButton::HDButton(const QString &text, QWidget *parent):QPushButton (text, parent)
{

}

HDButton::HDButton(const QIcon &icon, const QString &text, QWidget *parent):QPushButton (icon,text, parent)
{

}

void HDButton::mousePressEvent(QMouseEvent *e)
{
    //获取按钮的字符
    QString str = this->text();
    char ch = str.at(0).toLatin1();
    //创建按钮事件
    QKeyEvent *key = new QKeyEvent(QKeyEvent::KeyPress, ch,Qt::NoModifier,str);
    //发送事件
    QApplication::postEvent(QApplication::focusWidget(), key);//发送事件给获取焦点的窗口
}
