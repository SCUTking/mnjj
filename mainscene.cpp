#include "mainscene.h"
#include "ui_mainscene.h"
#include"qpainter.h"
#include"mypushbutton.h"
#include"QTimer"
#include"QDebug"
mainscene::mainscene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainscene)
{
    ui->setupUi(this);
    this->setFixedSize(2000,1200);
    this->setWindowTitle("模拟家居环境");
    //this->setWindowIcon();
    //房间的按钮 4个
    //载入4个designscene
    designb=new designscene;
    designk=new designscene;
    designl=new designscene;
    designw=new designscene;
    //卧室
    mypushbutton* room1=new mypushbutton(":/mainscene/mnjj/mainscene/bedroom.png");//路径这么写
    room1->setParent(this);
    //设置气泡
    room1->setFixedSize(800,600);
    room1->setIconSize(QSize(800,600));
    room1->setToolTip("卧室");
    room1->setToolTipDuration(30000);
    room1->move(400, 0);
    connect(room1, &mypushbutton::clicked, [=]() {
        room1->zoom1();
        room1->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            this->hide();
            designb->show();

        });
    });
    connect(designb->back,&mypushbutton::clicked,[=](){
        designb->back->zoom1();
        designb->back->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            //this->hide();
            designb->hide();
            this->show();
        });
    });
    //厨房
    mypushbutton* room2=new mypushbutton(":/mainscene/mnjj/mainscene/kitchen.png");//路径这么写
    room2->setParent(this);
    //设置气泡
    room2->setFixedSize(800,600);
    room2->setToolTip("厨房");
    room2->setToolTipDuration(30000);
    room2->move(400, 600);
    connect(room2, &mypushbutton::clicked, [=]() {
        room2->zoom1();
        room2->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            this->hide();
            designk->show();
        });
    });
    connect(designk->back,&mypushbutton::clicked,[=](){
        designk->back->zoom1();
        designk->back->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            //this->hide();
            designk->hide();
            this->show();
        });
    });
    //客厅
    mypushbutton* room3=new mypushbutton(":/mainscene/mnjj/mainscene/livingroom.png");//路径这么写
    room3->setParent(this);
    //设置气泡
    room3->setFixedSize(800,600);
    room3->setIconSize(QSize(800,600));
    room3->setToolTip("客厅");
    room3->setToolTipDuration(30000);
    room3->move(1200, 0);
    connect(room3, &mypushbutton::clicked, [=]() {
        room3->zoom1();
        room3->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            this->hide();
            designl->show();
        });
    });
    connect(designl->back,&mypushbutton::clicked,[=](){
        designl->back->zoom1();
        designl->back->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            //this->hide();
            designl->hide();
            this->show();
        });
    });
    //洗手间
    mypushbutton* room4=new mypushbutton(":/mainscene/mnjj/mainscene/washroom.png");//路径这么写
    room4->setParent(this);
    //设置气泡
    room4->setFixedSize(800,600);
    room4->setIconSize(QSize(800,600));
    room4->setToolTip("洗手间");
    room4->setToolTipDuration(30000);
    room4->move(1200, 600);
    connect(room4, &mypushbutton::clicked, [=]() {


        room4->zoom1();
        room4->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            this->hide();
            designw->show();
        });
    });
    connect(designw->back,&mypushbutton::clicked,[=](){
        designw->back->zoom1();
        designw->back->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            //this->hide();
            designw->hide();
            this->show();
        });
    });

    //载入img
    loadimg();
    //载入按钮
    loadbutton();


}
void mainscene::loadbutton(){
    //返回控件

    mypushbutton* newwind=new mypushbutton(":/mainscene/mnjj/mainscene/newwind.png");//在开头定义
    mypushbutton* dinuan=new mypushbutton(":/mainscene/mnjj/mainscene/dinuan.png");
    mypushbutton* tembtn=new mypushbutton(":/mainscene/mnjj/mainscene/tem.png");
    mypushbutton* humbtn=new mypushbutton(":/mainscene/mnjj/mainscene/hum.png");
    mypushbutton* qulbtn=new mypushbutton(":/mainscene/mnjj/mainscene/qul.png");








    newwind->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    newwind->setStyleSheet("QPushButton:hover{border-image: url(:/mainscene/mnjj/mainscene/newwind.png);background-color:#aaaaaa;}");
    newwind->setParent(this);//ui->widget在design上面
    newwind->move(0,0);//按钮的高度与ok1-》height不同
    newwind->setFixedSize(80,60);
    newwind->setIconSize(QSize(80,60));
    connect(newwind, &mypushbutton::clicked, [=]() {
        newwind->zoom1();
        newwind->zoom2();
        nwind=new designnewwind(this);
        nwind->isnewwind=1;//点击后，默认打开
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            //this->hide();
            nwind->show();
            no->hide();
            humbtn->hide();
            qulbtn->hide();
            tembtn->hide();
            dinuan->hide();
            newwind->hide();

            connect(nwind->no, &mypushbutton::clicked, [=]() {
                nwind->no->zoom1();
                nwind->no->zoom2();
                //延时进入下一个场景
                QTimer::singleShot(500,this,[=](){
                     delete nwind;//不能写temimg-》hide；否则会报错
                     humbtn->show();
                     qulbtn->show();
                     tembtn->show();
                     dinuan->show();
                     newwind->show();
                     no->show();
                });
                });

            connect(nwind->ok1, &mypushbutton::clicked, [=]() {
                nwind->ok1->zoom1();
                nwind->ok1->zoom2();
                //延时进入下一个场景
                QTimer::singleShot(500,this,[=](){
                     delete nwind;//不能写temimg-》hide；否则会报错
                     humbtn->show();
                     qulbtn->show();
                     tembtn->show();
                     dinuan->show();
                     newwind->show();
                     no->show();
                });
                });
        });
    });

    dinuan->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    dinuan->setStyleSheet("QPushButton:hover{border-image: url(:/mainscene/mnjj/mainscene/dinuan.png);background-color:#aaaaaa;}");
    dinuan->setParent(this);//ui->widget在design上面
    dinuan->move(0,100);//按钮的高度与ok1-》height不同
    dinuan->setFixedSize(80,60);
    dinuan->setIconSize(QSize(80,60));
    connect(dinuan, &mypushbutton::clicked, [=]() {
        dinuan->zoom1();
        dinuan->zoom2();
        dnuan=new designdinuan(this);
        dnuan->isdinuan=1;//点击后，默认打开
        //dnuan->exec();//QDialog的函数，模态对话框

        //connect(dnuan,&dnuan->Tx_NewSig,this,&MainWindow::Rx_NewSig);//绑定当前界面的信号槽
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            //this->hide();
            dnuan->show();
            no->hide();
            humbtn->hide();
            qulbtn->hide();
            tembtn->hide();
            dinuan->hide();
            newwind->hide();

            connect(dnuan->no, &mypushbutton::clicked, [=]() {
                dnuan->no->zoom1();
                dnuan->no->zoom2();
                //延时进入下一个场景
                QTimer::singleShot(500,this,[=](){
                     delete dnuan;//不能写temimg-》hide；否则会报错
                     humbtn->show();
                     qulbtn->show();
                     tembtn->show();
                     dinuan->show();
                     newwind->show();
                     no->show();
                });
                });

            connect(dnuan->ok1, &mypushbutton::clicked, [=]() {
                dnuan->ok1->zoom1();
                dnuan->ok1->zoom2();
                //延时进入下一个场景
                QTimer::singleShot(500,this,[=](){
                     delete dnuan;//不能写temimg-》hide；否则会报错
                     humbtn->show();
                     qulbtn->show();
                     tembtn->show();
                     dinuan->show();
                     newwind->show();
                     no->show();
                });
                });

        });

    });







    tembtn->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    tembtn->setStyleSheet("QPushButton:hover{border-image: url(:/mainscene/mnjj/mainscene/tem.png);background-color:#aaaaaa;}");
    tembtn->setParent(this);//ui->widget在design上面
    tembtn->move(0,200);//按钮的高度与ok1-》height不同
    tembtn->setFixedSize(80,60);
    tembtn->setIconSize(QSize(80,60));
    connect(tembtn, &mypushbutton::clicked, [=]() {
        tembtn->zoom1();
        tembtn->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
           temimg=new temimage(this,designk,designl,designw,designb);//特定时候才初始化，同时将该括号外的temimg移到括号里面
           no->hide();
           // this->hide();
            temimg->show();
            humbtn->hide();
            qulbtn->hide();
            tembtn->hide();
            dinuan->hide();
            newwind->hide();
            connect(temimg->no, &mypushbutton::clicked, [=]() {
                temimg->no->zoom1();
                temimg->no->zoom2();
                no->show();
                //延时进入下一个场景
                QTimer::singleShot(500,this,[=](){

                     delete temimg;//不能写temimg-》hide；否则会报错

                     humbtn->show();
                     qulbtn->show();
                     tembtn->show();
                     dinuan->show();
                     newwind->show();
                });
                });
        });
    });





    humbtn->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    humbtn->setStyleSheet("QPushButton:hover{border-image: url(:/mainscene/mnjj/mainscene/hum.png);background-color:#aaaaaa;}");
    humbtn->setParent(this);//ui->widget在design上面
    humbtn->move(0,300);//按钮的高度与ok1-》height不同
    humbtn->setFixedSize(80,60);
    humbtn->setIconSize(QSize(80,60));
    connect(humbtn, &mypushbutton::clicked, [=]() {
        humbtn->zoom1();
        humbtn->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            //->hide();
            humimg=new humimage(this,designk,designl,designw,designb);
            no->hide();
            humimg->show();
            humbtn->hide();
            qulbtn->hide();
            tembtn->hide();
            dinuan->hide();
            newwind->hide();
            connect(humimg->no, &mypushbutton::clicked, [=]() {

                humimg->no->zoom1();
                humimg->no->zoom2();
                //延时进入下一个场景
                QTimer::singleShot(500,this,[=](){

                    delete humimg;
                    //humimg->hide();
                    no->show();

                     humbtn->show();
                     qulbtn->show();
                     tembtn->show();
                     dinuan->show();
                     newwind->show();
                });
                });

        });
    });







    qulbtn->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    qulbtn->setStyleSheet("QPushButton:hover{border-image: url(:/mainscene/mnjj/mainscene/dinuan.png);background-color:#aaaaaa;}");
    qulbtn->setParent(this);//ui->widget在design上面
    qulbtn->move(0,400);//按钮的高度与ok1-》height不同
    qulbtn->setFixedSize(80,60);
    qulbtn->setIconSize(QSize(80,60));
    connect(qulbtn, &mypushbutton::clicked, [=]() {
        qulbtn->zoom1();
        qulbtn->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            //qDebug()<<"1";
            quaimg=new qualityimage(this,designk,designl,designw,designb);
            //this->hide();
            quaimg->show();
            no->hide();
            humbtn->hide();
            qulbtn->hide();
            tembtn->hide();
            dinuan->hide();
            newwind->hide();
            connect(quaimg->no, &mypushbutton::clicked, [=]() {
                quaimg->no->zoom1();
                quaimg->no->zoom2();

                //延时进入下一个场景
                QTimer::singleShot(500,this,[=](){


                    delete quaimg;



                        no->show();
                     humbtn->show();
                     qulbtn->show();
                     tembtn->show();
                     dinuan->show();
                     newwind->show();
                });
                });

        });
    });

    //返回按钮

    no=new mypushbutton(":/design/mnjj/design/nored.png");
    no->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    no->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    no->setParent(this);//ui->widget在design上面
    no->move(0,500);//按钮的高度与ok1-》height不同 用ok1的数据
    no->setFixedSize(80,60);
    no->setIconSize(QSize(80,60));


}




mainscene::~mainscene()
{
    delete ui;
}


void mainscene::loadimg()
{

    }
