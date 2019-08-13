#ifndef HDBUTTON_H
#define HDBUTTON_H

#include <QObject>
#include <QPushButton>
class HDButton : public QPushButton
{
public:
    explicit HDButton(QWidget *parent = nullptr);
    explicit HDButton(const QString &text, QWidget *parent = nullptr);
    HDButton(const QIcon& icon, const QString &text, QWidget *parent = nullptr);

    //实现鼠标点击事件
    void  mousePressEvent(QMouseEvent *e);
};

#endif // HDBUTTON_H
