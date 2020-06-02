#include "widget.h"
#include "ui_widget.h"
#include "mybtn.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    myBtn * btn = new myBtn(this);
    btn->setText("按钮");

    btn->resize(500,100);

}

Widget::~Widget()
{
    delete ui;
}

