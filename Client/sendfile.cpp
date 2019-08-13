#include "sendfile.h"
#include "ui_sendfile.h"
#include "menu.h"
#include <QHostAddress>
#include <QPixmap>
#include <iostream>
#include <fstream>
#include <QtAndroid>
#include <QAndroidJniObject>

QString selectedFileName;

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL
Java_com_amin_QtAndroidGallery_QtAndroidGallery_fileSelected(JNIEnv */*env*/,
                                                             jobject /*obj*/,
                                                             jstring results)
{
    selectedFileName = QAndroidJniObject(results).toString();
}

#ifdef __cplusplus
}
#endif


SendFile::SendFile(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SendFile)
{
    ui->setupUi(this);

}

SendFile::~SendFile()
{
    delete ui;
}

void SendFile::on_backBt_clicked()
{
    //返回到主界面
    this->parentWidget()->show();
    //本窗口销毁
    delete this;
}

void SendFile::on_imageBt_pressed()
{ selectedFileName = "#";
    QAndroidJniObject::callStaticMethod<void>("com/amin/QtAndroidGallery/QtAndroidGallery",
                                              "openAnImage",
                                              "()V");
    while(selectedFileName == "#")
        qApp->processEvents();
    qDebug()<<"************selectedFileName "<<selectedFileName;
    QFile img;
    img.setFileName(selectedFileName);

    if(img.exists())
    {
        QImage img(selectedFileName);
        qDebug()<<"***********************img "<<img;
        ui->label->setPixmap(QPixmap::fromImage(img));
    }

}





















