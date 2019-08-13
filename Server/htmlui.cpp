#include "htmlui.h"
#include "ui_htmlui.h"
#include <QAxWidget>

HtmlUI::HtmlUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HtmlUI)
{
    ui->setupUi(this);
    ui->axWidget->setControl(QString::fromUtf8("{8856F961-340A-11D0-A96B-00C04FD705A2}")); //设置插件为IE
    ui->axWidget->dynamicCall("Navigate(const QString&)", "http://101.201.233.215:8080/JasonBlog/"); //调用参数
    //ui->axWidget->setControl("E:\\QT\\RemoteContrl\\2.docx");
}

HtmlUI::~HtmlUI()
{
    delete ui;
}

void HtmlUI::on_pushButton_clicked()
{
    this->parentWidget()->show();
    delete this;
}
