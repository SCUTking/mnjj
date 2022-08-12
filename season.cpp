#include "season.h"
#include "ui_season.h"
#include"QTimer"
int season::whichseason=1;//默认夏季
season::season(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::season)
{
    ui->setupUi(this);
    setbutton();

}
void season::setbutton(){
 mscene=new mainscene;

    no=new mypushbutton(":/design/mnjj/design/no.png");
    no->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    no->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    no->setParent(this);//ui->widget在design上面
    no->move(1800,5);//按钮的高度与ok1-》height不同 用ok1的数据
    no->setFixedSize(80,60);
    no->setIconSize(QSize(80,60));
    //返回的




    mypushbutton* season1=new mypushbutton(":/mainscene/mnjj/mainscene/spring.png");//路径这么写
    season1->setParent(this);
    //设置气泡
    season1->setFixedSize(565,565);
    season1->setIconSize(QSize(565,565));
    season1->setToolTip("春");
    season1->setToolTipDuration(30000);
    season1->move(435,70);
    connect(season1, &mypushbutton::clicked, [=]() {
        season1->zoom1();
        season1->zoom2();
        //延时进入下一个场景
        whichseason=0;
        QTimer::singleShot(500,this,[=](){
            //延时进入下一个场景

            this->hide();
            mscene->show();
        });
    });

    mypushbutton* season2=new mypushbutton(":/mainscene/mnjj/mainscene/summer.png");//路径这么写
    season2->setParent(this);
    //设置气泡
    season2->setFixedSize(565,565);
    season2->setIconSize(QSize(565,565));
    season2->setToolTip("夏");
    season2->setToolTipDuration(30000);
    season2->move(1000,70);
    connect(season2, &mypushbutton::clicked, [=]() {
        season2->zoom1();
        season2->zoom2();
        //延时进入下一个场景
        whichseason=1;

        QTimer::singleShot(500,this,[=](){
            //延时进入下一个场景
            this->hide();
            mscene->show();
        });
    });

    mypushbutton* season3=new mypushbutton(":/mainscene/mnjj/mainscene/fall.png");//路径这么写
    season3->setParent(this);
    //设置气泡
    season3->setFixedSize(565,565);
    season3->setIconSize(QSize(565,565));
    season3->setToolTip("秋");
    season3->setToolTipDuration(30000);
    season3->move(435,635);
    connect(season3, &mypushbutton::clicked, [=]() {
        season3->zoom1();
        season3->zoom2();
        //延时进入下一个场景
        whichseason=2;

        QTimer::singleShot(500,this,[=](){
            //延时进入下一个场景
            this->hide();
            mscene->show();
        });
    });

    mypushbutton* season4=new mypushbutton(":/mainscene/mnjj/mainscene/winter.png");//路径这么写
    season4->setParent(this);
    //设置气泡
    season4->setFixedSize(565,565);
    season4->setIconSize(QSize(565,565));
    season4->setToolTip("冬");
    season4->setToolTipDuration(30000);
    season4->move(1000,635);
    connect(season4, &mypushbutton::clicked, [=]() {
        season4->zoom1();
        season4->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            //延时进入下一个场景
                    whichseason=3;
            this->hide();
            mscene->show();
        });
    });

    connect(mscene->no, &mypushbutton::clicked, [=]() {
        mscene->no->zoom1();
        mscene->no->zoom2();
        //延时进入下一个场景


        QTimer::singleShot(500,this,[=](){

        mscene->hide();
        this->show();
        });
        });
}

season::~season()
{
    delete ui;
}
