#ifndef SENDFILE_H
#define SENDFILE_H

#include <QMainWindow>
#include <QUdpSocket>

namespace Ui {
class SendFile;
}

class SendFile : public QMainWindow
{
    Q_OBJECT

public:
    explicit SendFile(QWidget *parent = nullptr);
    ~SendFile();
    void sendImage(QPixmap mPix);

private slots:
    void on_imageBt_pressed();
    void on_backBt_clicked();

private:
    Ui::SendFile *ui;

};

#endif // SENDFILE_H
