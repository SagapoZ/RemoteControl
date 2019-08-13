#ifndef HTMLUI_H
#define HTMLUI_H

#include <QMainWindow>

namespace Ui {
class HtmlUI;
}

class HtmlUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit HtmlUI(QWidget *parent = nullptr);
    ~HtmlUI();

private slots:
    void on_pushButton_clicked();

private:
    Ui::HtmlUI *ui;
};

#endif // HTMLUI_H
