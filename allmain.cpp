#include "allmain.h"
#include "ui_allmain.h"
#include"qpainter.h"
#include"mypushbutton.h"
#include"QTimer"



Allmain::Allmain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Allmain)
{
    ui->setupUi(this);
    this->setFixedSize(2000,1200);//默认大小
    this->setWindowTitle("模拟家居环境");
    this->setWindowIcon(QPixmap(":/mnjj/allmain/windowicon1.png"));
    //设置label 的4个图片
    QPixmap pix;
    pix.load(":/mnjj/allmain/label1.png");//单独的pix.scaled(800,600)没有什么用得在前面加
    pix=pix.scaled(800,600);
    ui->label1->setPixmap(pix);

    pix.load(":/mnjj/allmain/label2.png");
    pix=pix.scaled(800,600);
    ui->label2->setPixmap(pix);

    pix.load(":/mnjj/allmain/label3.png");
     pix=pix.scaled(800,600);
    ui->label3->setPixmap(QPixmap(pix));

    pix.load(":/mnjj/allmain/label4.png");
    pix=pix.scaled(800,600);
    ui->label4->setPixmap(QPixmap(pix));

    //new其他的场景

    citychoose=new choose_city;
    //开始按钮
    mypushbutton* startbtn=new mypushbutton(":/mnjj/allmain/start.png");//
     startbtn->setParent(this);
       //设置气泡
       startbtn->setToolTip("开始按钮");
       startbtn->setToolTipDuration(30000);
       startbtn->move(this->width()- startbtn->width(), this->height() * 0.7);
       connect(startbtn, &mypushbutton::clicked, [=]() {
           startbtn->zoom1();
           startbtn->zoom2();
           //延时进入下一个场景
           QTimer::singleShot(500,this,[=](){
               this->hide();
              citychoose->show();
           });


           });
       connect(citychoose->no, &mypushbutton::clicked, [=]() {
           citychoose->no->zoom1();
           citychoose->no->zoom2();
           //延时进入下一个场景
           QTimer::singleShot(500,this,[=](){
               citychoose->hide();
               this->show();
           });
       });


      //退出按钮
        mypushbutton* endbtn=new mypushbutton(":/mnjj/allmain/end.png");
        endbtn->setParent(this);
        //气泡
        endbtn->setToolTip("退出按钮");
        endbtn->setToolTipDuration(30000);
        endbtn->move(this->width()-endbtn->width(), this->height()*0.5);
        connect(endbtn, &mypushbutton::clicked, [=]() {
        endbtn->zoom1();
        endbtn->zoom2();
        QTimer::singleShot(500,this,[=](){
           this->close();
        });
              });
}

Allmain::~Allmain()
{
    delete ui;
}
void Allmain::paintEvent(QPaintEvent*) {//画背景图
    //绘制背景图
    QPainter painter(this);
    QPixmap pix;
   //pix.load(":/mnjj/allmain/background1.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}

