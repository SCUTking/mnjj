#include "designscene.h"
#include "ui_designscene.h"
#include"mypushbutton.h"
#include"QString"
#include"QTimer"
#include"QIcon"
#include"object.h"
#include"temimage.h"
#include"ui_designroom.h"
#include "ui_designair.h"//加上这句化可以在该类访问其他类的ui文件的控件，必须将其他类的ui设为public；**************
designscene::designscene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::designscene)
{




    ui->setupUi(this);
    this->setFixedSize(2000,1200);
    this->setWindowTitle("模拟家居环境");



    /*ui->lineEdit->SetUnitText("m");
ui->lineEdit->setStyleSheet("border-radius:5px;"//设置圆角边框
                            "background-color:#ffffff;"//设计背景色
                            //"margin:10px;"//优化边缘
                            "border:3px solid #abc;"//优化边框（边框有纹路）
                            "padding: 5px;"//下面三行优化输入内容
                            "padding-left: 15px;"
                            "padding-right: 15px;"
                            );*/
    //返回控件
    back=new mypushbutton(":/design/mnjj/design/no.png");
    back->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    back->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    back->setParent(this);//ui->widget在design上面
    back->move(1650,20);//按钮的高度与ok1-》height不同
    back->setFixedSize(80,60);
    back->setIconSize(QSize(80,60));
    connect(back, &mypushbutton::clicked, [=]() {
        //按返回健时获取数据
        int l=room->ui->lineEdit->text().toDouble();
        int w=room->ui->lineEdit_2->text().toDouble();
        int h=room->ui->lineEdit_3->text().toDouble();
        if(l!=0&&w!=0&&h!=0){
            roomv=l*w*h;
            rooms=(l*w+l*h+w*h)*2;
        }

        airk=airnums[airwhich];
        airtwok=airtwonums[airtwowhich];
        roomk=roomnums[roomwhich];
        roomwidthk=roomwidth;
        humk=humnums[humwhich];
        dehumk=dehumnums[dehumwhich];
        });




    //QPixmap pix1;
    //pix1.load(":/mnjj/allmain/label1.png");//单独的pix.scaled(800,600)没有什么用得在前面加
    //pix1=pix1.scaled(80,60);


    loadres();



    //QLineEdit* lineedit,mypushbutton* putton,QLabel* picture,QString stringpix（图片路劲）
    //(改变图片的大小）注意先预先设置好足够且恰当的qlabel
    //changepicture1(ui->lineEdit,room1,ui->label,":/mnjj/allmain/label1.png");


}
void designscene::loadres()
{


    int iconsizewidth=300;
    int iconsizeheight=200;

    //载入界面
    //载入界面
    dairtwo=new airtwo(this,&this->airtwowhich);
    air=new designair(this,&this->airwhich,&this->checktem);
    room=new designroom(this,&this->roomwhich,&roomwidth);
    dbed=new designbed;
    dtv=new designtv;
    dcase=new designcase;
    ddesk=new designdesk(this);
    dfridge=new frigde(this);
    dhumidifier=new humidifier(this,&this->humwhich,&this->checkmin);
    ddehumidifier=new dehumidifier(this,&this->dehumwhich,&this->checkmax);
    //dknife=new designknife(this);//可以使用同一个ui类对象，只是要new分配内存


    //载入房间设计界面
    mypushbutton* roombtn=new mypushbutton(":/design/mnjj/design/room.png");
    //roombtn->isactive=1;
    QPixmap pix;
    pix.load(":/design/mnjj/design/room.png");//单独的pix.scaled(800,600)没有什么用得在前面加
    //double c=air->ui->lineEdit->text().toDouble();
    //double k=air->ui->lineEdit_2->text().toDouble();
    //double g=air->ui->lineEdit_3->text().toDouble();
    pix=pix.scaled(1400,1200);
    roombtn->setFixedSize(pix.width(), pix.height());//设置按钮大小
    roombtn->setIconSize(QSize(pix.width(), pix.height()));

    roombtn->setIcon(pix);
    roombtn->setParent(this);
    //设置气泡
    roombtn->setToolTip("添加空调");
    roombtn->setToolTipDuration(30000);
    roombtn->move(0, 0);
    connect(roombtn, &mypushbutton::clicked, [=]() {
        roombtn->zoom1();
        roombtn->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            room->setParent(this);
            room->setStyleSheet("background-color:#ffffff;"
                                "border-radius:5px;"//设置圆角边框
                                "border:3px solid #abc;"//优化边框（边框有纹路）
                                );
            room->move(1400,0);
            room->show();
            air->hide();
        });
    });

    //载入冰箱设计界面



    mypushbutton* fridgebtn=new mypushbutton(":/design/mnjj/design/fridge.png");
   fridgebtn->setFixedSize(300,200);
    fridgebtn->setIconSize(QSize(300, 200));//设置图标大小
    fridgebtn->isactive=0;
    fridgebtn->setParent(ui->scrollAreaWidgetContents);
    //设置气泡
    fridgebtn->setToolTip("冰箱");
    fridgebtn->setToolTipDuration(30000);
    fridgebtn->move(0, iconsizeheight*13);//空调
    connect(fridgebtn, &mypushbutton::clicked, [=]() {

        fridgebtn->zoom1();
        fridgebtn->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){

            if(work30==1){
                fridgetrue=new mypushbutton(":/design/mnjj/design/fridge.png");

                copy(this,fridgetrue,"冰箱",dfridge);


                work30=0;
            }
            if(work30==0){
                fridgetrue->show();
                work30=2;
            }
        });
    });
    connect(dfridge->cut, &mypushbutton::clicked, [=]() {
        //air->cut->zoom1();
        //air->cut->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            fridgetrue->hide();
            dfridge->hide();
            work30=0;
            room->hide();
        });
    });























    //载入加湿器设计界面


    mypushbutton* humidifierbtn=new mypushbutton(":/design/mnjj/design/humidifier.png");
   humidifierbtn->setFixedSize(300,200);
    humidifierbtn->setIconSize(QSize(300, 200));//设置图标大小
    humidifierbtn->isactive=0;
    humidifierbtn->setParent(ui->scrollAreaWidgetContents);
    //设置气泡
    humidifierbtn->setToolTip("加湿器");
    humidifierbtn->setToolTipDuration(30000);
    humidifierbtn->move(iconsizewidth, iconsizeheight*13);//空调
    connect(humidifierbtn, &mypushbutton::clicked, [=]() {

        humidifierbtn->zoom1();
        humidifierbtn->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){

            if(work31==1){
                humidifiertrue=new mypushbutton(":/design/mnjj/design/humidifier.png");

                copy(this,humidifiertrue,"加湿器",dhumidifier);
                ifhum=1;

                work31=0;
            }
            if(work31==0){
                humidifiertrue->show();
                ifhum=1;
                work31=2;
            }
        });
    });
    connect(dhumidifier->cut, &mypushbutton::clicked, [=]() {
        //air->cut->zoom1();
        //air->cut->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            humidifiertrue->hide();
            dhumidifier->hide();
            ifhum=0;
            work31=0;
            room->hide();
        });
    });


    //载入加湿器设计界面


    mypushbutton* dehumidifierbtn=new mypushbutton(":/design/mnjj/design/dehumidifer.png");
   dehumidifierbtn->setFixedSize(300,200);
    dehumidifierbtn->setIconSize(QSize(300, 200));//设置图标大小
    dehumidifierbtn->isactive=0;
    dehumidifierbtn->setParent(ui->scrollAreaWidgetContents);
    //设置气泡
    dehumidifierbtn->setToolTip("除湿器");
    dehumidifierbtn->setToolTipDuration(30000);
    dehumidifierbtn->move(0, iconsizeheight*14);//空调
    connect(dehumidifierbtn, &mypushbutton::clicked, [=]() {

        dehumidifierbtn->zoom1();
        dehumidifierbtn->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){

            if(work32==1){
                dehumidifiertrue=new mypushbutton(":/design/mnjj/design/dehumidifer.png");

                copy(this,dehumidifiertrue,"除湿器",ddehumidifier);
                ifdehum=1;

                work32=0;
            }
            if(work32==0){
                dehumidifiertrue->show();
                 ifdehum=1;
                work32=2;
            }
        });
    });
    connect(ddehumidifier->cut, &mypushbutton::clicked, [=]() {
        //air->cut->zoom1();
        //air->cut->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            dehumidifiertrue->hide();
            ddehumidifier->hide();
             ifdehum=0;
            work32=0;
            room->hide();
        });
    });
    //载入柜式空调设计界面


    mypushbutton* airtwobtn=new mypushbutton(":/design/mnjj/design/airtwo.png");
    airtwobtn->setFixedSize(300,200);
    airtwobtn->setIconSize(QSize(300, 200));//设置图标大小
    airtwobtn->isactive=0;
    airtwobtn->setParent(ui->scrollAreaWidgetContents);
    //设置气泡
    airtwobtn->setToolTip("柜式空调");
    airtwobtn->setToolTipDuration(30000);
    airtwobtn->move(iconsizewidth, iconsizeheight*14);//空调
    connect(airtwobtn, &mypushbutton::clicked, [=]() {

        airtwobtn->zoom1();
        airtwobtn->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){

            if(work40==1){
                airtwotrue=new mypushbutton(":/design/mnjj/design/airtwo.png");

                copy(this,airtwotrue,"柜式空调",dairtwo);

                work40=0;

                ifairtwo=1;

            }
            if(work40==0){
                airtwotrue->show();

                ifairtwo=1;

                work40=2;
            }
        });
    });
    connect(dairtwo->cut, &mypushbutton::clicked, [=]() {
        //air->cut->zoom1();
        //air->cut->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            airtwotrue->hide();
            dairtwo->hide();
            work40=0;

            ifairtwo=0;

            room->hide();
        });
    });



    //载入空调设计界面



    mypushbutton* airbtn=new mypushbutton(":/design/mnjj/design/air.png");
    airbtn->setFixedSize(300,200);
    airbtn->setIconSize(QSize(300, 200));//设置图标大小
    airbtn->isactive=0;
    airbtn->setParent(ui->scrollAreaWidgetContents);
    //设置气泡
    airbtn->setToolTip("挂式空调");
    airbtn->setToolTipDuration(30000);
    airbtn->move(0, 0);//空调
    connect(airbtn, &mypushbutton::clicked, [=]() {

        airbtn->zoom1();
        airbtn->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){

            if(work==1){
                airtrue=new mypushbutton(":/design/mnjj/design/air.png");

                copy(this,airtrue,"挂式空调",air);
ifair=1;
                work=0;
            }
            if(work==0){
                airtrue->show();
                ifair=1;

                work=2;
            }
        });
    });
    connect(air->cut, &mypushbutton::clicked, [=]() {
        //air->cut->zoom1();
        //air->cut->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            airtrue->hide();
            air->hide();
            work=0;
            ifair=0;

            room->hide();
        });
    });




















    //载入床头柜

    mypushbutton* desk=new mypushbutton(":/design/mnjj/design/desk.png");//
    desk->setFixedSize(300,200);
    desk->setIconSize(QSize(300, 200));
    desk->setParent(ui->scrollAreaWidgetContents);
    //设置气泡
    desk->setToolTip("床头桌");
    desk->setToolTipDuration(30000);
    desk->move(300, 0);//空调
    connect(desk, &mypushbutton::clicked, [=]() {
        desk->zoom1();
        desk->zoom2();
        ifwindow=1;
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){

            if(work1==1){
                desktrue=new mypushbutton(":/design/mnjj/design/desk.png");
                copy(this,desktrue,"空调",ddesk);
                work1=0;
            }
            if(work1==0){
                desktrue->show();
                work1=2;
            }
        });
    });
    connect(ddesk->cut, &mypushbutton::clicked, [=]() {
        ddesk->cut->zoom1();
        ddesk->cut->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            desktrue->hide();
            ddesk->hide();
            work1=0;
            room->hide();
            ifwindow=0;
        });
    });



    //载入电视机

    mypushbutton* tv=new mypushbutton(":/design/mnjj/design/tv.png");//
    tv->setFixedSize(300,200);
    tv->setIconSize(QSize(300, 200));
    tv->setParent(ui->scrollAreaWidgetContents);
    //设置气泡
    tv->setToolTip("电视机");
    tv->setToolTipDuration(30000);
    tv->move(0, 200);//空调
    connect(tv, &mypushbutton::clicked, [=]() {
        tv->zoom1();
        tv->zoom2();
        ifTV=1;

        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            if(work2==1){
                tvtrue=new mypushbutton(":/design/mnjj/design/tv.png");
                copy(this,tvtrue,"空调",dtv);
                work2=0;
            }
            if(work2==0){
                tvtrue->show();
                work2=2;
            }
        });
    });
    connect(dtv->cut, &mypushbutton::clicked, [=]() {
        dtv->cut->zoom1();
        dtv->cut->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            tvtrue->hide();
            dtv->hide();
            work2=0;
            room->hide();
            ifTV=0;

        });
    });
    //载入床

    mypushbutton* bed=new mypushbutton(":/design/mnjj/design/bed.png");//
    bed->setParent(ui->scrollAreaWidgetContents);
    bed->setIconSize(QSize(300, 200));
    bed->setFixedSize(300,200);
    //设置气泡
    bed->setToolTip("床");
    bed->setToolTipDuration(30000);
    bed->move(300, 200);//空调
    connect(bed, &mypushbutton::clicked, [=]() {
        bed->zoom1();
        bed->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            //static int work3=1;//只进行一次
            if(work3==1){
                bedtrue=new mypushbutton(":/design/mnjj/design/bed.png");
                //airtrue->setFixedSize(300,200);
                //airtrue->setIconSize(QSize(300, 200));//设置图标大小
                copy(this,bedtrue,"空调",dbed);
                work3=0;
            }
            if(work3==0){
                bedtrue->show();
                work3=2;
            }
        });
    });
    connect(dbed->cut, &mypushbutton::clicked, [=]() {
        dbed->cut->zoom1();
        dbed->cut->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            bedtrue->hide();
            dbed->hide();
            work3=0;
            room->hide();
        });
    });
    //载入花瓶(需要在头文件加入相应的design界面，独一无二的）//300，200

    mypushbutton* fcase=new mypushbutton(":/design/mnjj/design/case.png");//
    fcase->setParent(ui->scrollAreaWidgetContents);
    fcase->setIconSize(QSize(300, 200));
    fcase->setFixedSize(300,200);
    //设置气泡
    fcase->setToolTip("花瓶");
    fcase->setToolTipDuration(30000);
    fcase->move(0, 400);//空调
    connect(fcase, &mypushbutton::clicked, [=]() {
        fcase->zoom1();
        fcase->zoom2();
        ifplant=1;
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            //static int work4=1;//只进行一次
            if(work4==1){
                fcasetrue=new mypushbutton(":/design/mnjj/design/case.png");
                copy(this,fcasetrue,"空调",dcase);
                work4=0;
            }
            if(work4==0){
                fcasetrue->show();
                work4=2;
            }
        });
    });
    connect(dcase->cut, &mypushbutton::clicked, [=]() {
        dcase->cut->zoom1();
        dcase->cut->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            fcasetrue->hide();
            dcase->hide();
            work4=0;
            room->hide();
            ifplant=0;

        });
    });
    //
    //普通物品的载入    继承designdesk
    /*
                                   * designdesk* dknife=NULL;
designdesk* dbowl=NULL;***
designdesk* dbowl1=NULL;***
designdesk* dclock=NULL;***
designdesk* dcooker=NULL;***
designdesk* deatdesk=NULL;***
designdesk* dlight=NULL;***
designdesk* dpan=NULL;***
designdesk* dplant=NULL;***
designdesk* dsalt=NULL;***
designdesk* dsark1=NULL;***
designdesk* dsark2=NULL;***
designdesk* dsark3=NULL;***
designdesk* dsark4=NULL;***
designdesk* dshower=NULL;***
designdesk* dsofa=NULL;***
designdesk* dstool=NULL;***
designdesk* dtea=NULL;***
designdesk* dwashbasin=NULL;***
designdesk* dwashcloth=NULL;***
designdesk* dwiredesk=NULL;
*/
    //刀具
    dknife=new designbed(this);

    mypushbutton* knife=new mypushbutton(":/design/mnjj/design/knife.png");//
    knife->setParent(ui->scrollAreaWidgetContents);
    knife->setIconSize(QSize(300, 200));
    knife->setFixedSize(300,200);
    //设置气泡
    knife->setToolTip("刀具");
    knife->setToolTipDuration(30000);
    knife->move(iconsizewidth,iconsizeheight*2);//空调
    connect(knife, &mypushbutton::clicked, [=]() {
        knife->zoom1();
        knife->zoom2();
        //延时进入下一个场景
        //qDebug()<<"ssssssss";
        QTimer::singleShot(500,this,[=](){
            //static int work4=1;//只进行一次
            if(work5==1){
                knifetrue=new mypushbutton(":/design/mnjj/design/knife.png");
                copy(this,knifetrue,"刀具",dknife);
                //qDebug()<<"asdasd";
                work5=0;
            }
            if(work5==0){
                knifetrue->show();
                work5=2;
            }
        });
    });
    connect(dknife->cut, &mypushbutton::clicked, [=]() {
        dknife->cut->zoom1();
        dknife->cut->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            knifetrue->hide();
            dknife->hide();
            work5=0;
            room->hide();
        });
    });


    //刀具
    dbowl=new designbed(this);

    mypushbutton* bowl=new mypushbutton(":/design/mnjj/design/bowl.png");
    bowl->setParent(ui->scrollAreaWidgetContents);
    bowl->setIconSize(QSize(300, 200));
    bowl->setFixedSize(300,200);
    //设置气泡
    bowl->setToolTip("碗");
    bowl->setToolTipDuration(30000);
    bowl->move(0,iconsizeheight*3);//空调
    connect(bowl, &mypushbutton::clicked, [=]() {
        bowl->zoom1();
        bowl->zoom2();
        //延时进入下一个场景
        //qDebug()<<"ssssssss";
        QTimer::singleShot(500,this,[=](){
            //static int work4=1;//只进行一次
            if(work6==1){
                bowltrue=new mypushbutton(":/design/mnjj/design/bowl.png");
                copy(this,bowltrue,"刀具",dbowl);
                //qDebug()<<"asdasd";
                work6=0;
            }
            if(work6==0){
                bowltrue->show();
                work6=2;
            }
        });
    });
    connect(dbowl->cut, &mypushbutton::clicked, [=]() {
        dbowl->cut->zoom1();
        dbowl->cut->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            bowltrue->hide();
            dbowl->hide();
            work6=0;
            room->hide();
        });
    });

    //碟子
    dbowl1=new designbed(this);

    mypushbutton* bowl1=new mypushbutton(":/design/mnjj/design/bowl1.png");//
    bowl1->setParent(ui->scrollAreaWidgetContents);
    bowl1->setIconSize(QSize(300, 200));
    bowl1->setFixedSize(300,200);
    //设置气泡
    bowl1->setToolTip("碟子");
    bowl1->setToolTipDuration(30000);
    bowl1->move(iconsizewidth,iconsizeheight*3);//空调
    connect(bowl1, &mypushbutton::clicked, [=]() {
        bowl1->zoom1();
        bowl1->zoom2();
        //延时进入下一个场景
        //qDebug()<<"ssssssss";
        QTimer::singleShot(500,this,[=](){
            //static int work4=1;//只进行一次
            if(work7==1){
                bowl1true=new mypushbutton(":/design/mnjj/design/bowl1.png");
                copy(this,bowl1true,"碟子",dbowl1);
                //qDebug()<<"asdasd";
                work7=0;
            }
            if(work7==0){
                bowl1true->show();
                work7=2;
            }
        });
    });
    connect(dbowl1->cut, &mypushbutton::clicked, [=]() {
        dbowl1->cut->zoom1();
        dbowl1->cut->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            bowl1true->hide();
            dbowl1->hide();
            work7=0;
            room->hide();
        });
    });

    //刀具
    dclock=new designbed(this);

    mypushbutton* clock=new mypushbutton(":/design/mnjj/design/clock.png");//
    clock->setParent(ui->scrollAreaWidgetContents);
    clock->setIconSize(QSize(300, 200));
    clock->setFixedSize(300,200);
    //设置气泡
    clock->setToolTip("刀具");
    clock->setToolTipDuration(30000);
    clock->move(0,iconsizeheight*4);//空调
    connect(clock, &mypushbutton::clicked, [=]() {
        clock->zoom1();
        clock->zoom2();
        //延时进入下一个场景
        //qDebug()<<"ssssssss";
        QTimer::singleShot(500,this,[=](){
            //static int work4=1;//只进行一次
            if(work8==1){
                clocktrue=new mypushbutton(":/design/mnjj/design/clock.png");
                copy(this,clocktrue,"时钟",dclock);
                //qDebug()<<"asdasd";
                work8=0;
            }
            if(work8==0){
                clocktrue->show();
                work8=2;
            }
        });
    });
    connect(dclock->cut, &mypushbutton::clicked, [=]() {
        dclock->cut->zoom1();
        dclock->cut->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            clocktrue->hide();
            dclock->hide();
            room->hide();
            work8=0;

        });
    });
    //
    //刀具
    dcooker=new designbed(this);

    mypushbutton* cooker=new mypushbutton(":/design/mnjj/design/cooker.png");//
    cooker->setParent(ui->scrollAreaWidgetContents);
    cooker->setIconSize(QSize(300, 200));
    cooker->setFixedSize(300,200);
    //设置气泡
    cooker->setToolTip("厨具");
    cooker->setToolTipDuration(30000);
    cooker->move(iconsizewidth,iconsizeheight*4);//空调
    connect(cooker, &mypushbutton::clicked, [=]() {
        cooker->zoom1();
        cooker->zoom2();
        //延时进入下一个场景
        //qDebug()<<"ssssssss";
        QTimer::singleShot(500,this,[=](){
            //static int work4=1;//只进行一次
            if(work9==1){
                cookertrue=new mypushbutton(":/design/mnjj/design/cooker.png");
                copy(this,cookertrue,"厨具",dcooker);
                //qDebug()<<"asdasd";
                work9=0;
            }
            if(work9==0){
                cookertrue->show();
                work9=2;
            }
        });
    });
    connect(dcooker->cut, &mypushbutton::clicked, [=]() {
        dcooker->cut->zoom1();
        dcooker->cut->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            cookertrue->hide();
            dcooker->hide();
            room->hide();
            work9=0;

        });
    });

    //饭桌
    deatdesk=new designbed(this);

    mypushbutton* eatdesk=new mypushbutton(":/design/mnjj/design/eatdesk.png");//
    eatdesk->setParent(ui->scrollAreaWidgetContents);
    eatdesk->setIconSize(QSize(300, 200));
    eatdesk->setFixedSize(300,200);
    //设置气泡
    eatdesk->setToolTip("饭桌");
    eatdesk->setToolTipDuration(30000);
    eatdesk->move(0,iconsizeheight*5);//空调
    connect(eatdesk, &mypushbutton::clicked, [=]() {
        eatdesk->zoom1();
        eatdesk->zoom2();
        //延时进入下一个场景
        //qDebug()<<"ssssssss";
        QTimer::singleShot(500,this,[=](){
            //static int work4=1;//只进行一次
            if(work10==1){
                eatdesktrue=new mypushbutton(":/design/mnjj/design/eatdesk.png");
                copy(this,eatdesktrue,"饭桌",deatdesk);
                //qDebug()<<"asdasd";
                work10=0;
            }
            if(work10==0){
                eatdesktrue->show();
                work10=2;
            }
        });
    });
    connect(deatdesk->cut, &mypushbutton::clicked, [=]() {
        deatdesk->cut->zoom1();
        deatdesk->cut->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            eatdesktrue->hide();
            deatdesk->hide();
            room->hide();
            work10=0;

        });
    });

    //灯
    dlight=new designbed(this);

    mypushbutton* light=new mypushbutton(":/design/mnjj/design/light.png");//
    light->setParent(ui->scrollAreaWidgetContents);
    light->setIconSize(QSize(300, 200));
    light->setFixedSize(300,200);
    //设置气泡
    light->setToolTip("灯");
    light->setToolTipDuration(30000);
    light->move(iconsizewidth,iconsizeheight*5);//空调
    connect(light, &mypushbutton::clicked, [=]() {
        light->zoom1();
        light->zoom2();
        //延时进入下一个场景
        //qDebug()<<"ssssssss";
        QTimer::singleShot(500,this,[=](){
            //static int work4=1;//只进行一次
            if(work11==1){
                lighttrue=new mypushbutton(":/design/mnjj/design/light.png");
                copy(this,lighttrue,"灯",dlight);
                //qDebug()<<"asdasd";
                work11=0;
            }
            if(work11==0){
                lighttrue->show();
                work11=2;
            }
        });
    });
    connect(dlight->cut, &mypushbutton::clicked, [=]() {
        dlight->cut->zoom1();
        dlight->cut->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            lighttrue->hide();
            dlight->hide();
            room->hide();
            work11=0;

        });
    });
    //锅
    dpan=new designbed(this);

    mypushbutton* pan=new mypushbutton(":/design/mnjj/design/pan.png");//
    pan->setParent(ui->scrollAreaWidgetContents);
    pan->setIconSize(QSize(300, 200));
    pan->setFixedSize(300,200);
    //设置气泡
    pan->setToolTip("锅");
    pan->setToolTipDuration(30000);
    pan->move(0,iconsizeheight*6);//空调
    connect(pan, &mypushbutton::clicked, [=]() {
        pan->zoom1();
        pan->zoom2();
        //延时进入下一个场景
        //qDebug()<<"ssssssss";
        QTimer::singleShot(500,this,[=](){
            //static int work4=1;//只进行一次
            if(work12==1){
                pantrue=new mypushbutton(":/design/mnjj/design/pan.png");
                copy(this,pantrue,"锅",dpan);
                //qDebug()<<"asdasd";
                work12=0;
            }
            if(work12==0){
                pantrue->show();
                work12=2;
            }
        });
    });
    connect(dpan->cut, &mypushbutton::clicked, [=]() {
        dpan->cut->zoom1();
        dpan->cut->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            pantrue->hide();
            dpan->hide();
            room->hide();
            work12=0;

        });
    });

    //壁画
    dplant=new designbed(this);

    mypushbutton* plant=new mypushbutton(":/design/mnjj/design/plant.png");//
    plant->setParent(ui->scrollAreaWidgetContents);
    plant->setIconSize(QSize(300, 200));
    plant->setFixedSize(300,200);
    //设置气泡
    plant->setToolTip("壁画");
    plant->setToolTipDuration(30000);
    plant->move(iconsizewidth,iconsizeheight*6);//空调
    connect(plant, &mypushbutton::clicked, [=]() {
        plant->zoom1();
        plant->zoom2();
        //延时进入下一个场景
        //qDebug()<<"ssssssss";
        QTimer::singleShot(500,this,[=](){
            //static int work4=1;//只进行一次
            if(work13==1){
                planttrue=new mypushbutton(":/design/mnjj/design/plant.png");
                copy(this,planttrue,"壁画",dplant);
                //qDebug()<<"asdasd";
                work13=0;
            }
            if(work13==0){
                planttrue->show();
                work13=2;
            }
        });
    });
    connect(dplant->cut, &mypushbutton::clicked, [=]() {
        dplant->cut->zoom1();
        dplant->cut->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            planttrue->hide();
            dplant->hide();
            room->hide();
            work13=0;

        });
    });

    //壁画
    dsalt=new designbed(this);

    mypushbutton* salt=new mypushbutton(":/design/mnjj/design/salt.png");//
    salt->setParent(ui->scrollAreaWidgetContents);
    salt->setIconSize(QSize(300, 200));
    salt->setFixedSize(300,200);
    //设置气泡
    salt->setToolTip("调料");
    salt->setToolTipDuration(30000);
    salt->move(0,iconsizeheight*7);//空调
    connect(salt, &mypushbutton::clicked, [=]() {
        salt->zoom1();
        salt->zoom2();
        //延时进入下一个场景
        //qDebug()<<"ssssssss";
        QTimer::singleShot(500,this,[=](){
            //static int work4=1;//只进行一次
            if(work14==1){
                salttrue=new mypushbutton(":/design/mnjj/design/salt.png");
                copy(this,salttrue,"调料",dsalt);
                //qDebug()<<"asdasd";
                work14=0;
            }
            if(work14==0){
               salttrue->show();
                work14=2;
            }
        });
    });
    connect(dsalt->cut, &mypushbutton::clicked, [=]() {
        dsalt->cut->zoom1();
        dsalt->cut->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            salttrue->hide();
            dsalt->hide();
            room->hide();
            work14=0;

        });
    });
    //壁画
    dsark1=new designbed(this);

    mypushbutton* sark1=new mypushbutton(":/design/mnjj/design/sark1.png");//
    sark1->setParent(ui->scrollAreaWidgetContents);
    sark1->setIconSize(QSize(300, 200));
    sark1->setFixedSize(300,200);
    //设置气泡
   sark1->setToolTip("柜子");
    sark1->setToolTipDuration(30000);
    sark1->move(iconsizewidth,iconsizeheight*7);//空调
    connect(sark1, &mypushbutton::clicked, [=]() {
        sark1->zoom1();
        sark1->zoom2();
        //延时进入下一个场景
        //qDebug()<<"ssssssss";
        QTimer::singleShot(500,this,[=](){
            //static int work4=1;//只进行一次
            if(work15==1){
                sark1true=new mypushbutton(":/design/mnjj/design/sark1.png");
                copy(this,sark1true,"柜子",dsark1);
                //qDebug()<<"asdasd";
                work15=0;
            }
            if(work15==0){
                sark1true->show();
                work15=2;
            }
        });
    });
    connect(dsark1->cut, &mypushbutton::clicked, [=]() {
        dsark1->cut->zoom1();
        dsark1->cut->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            sark1true->hide();
            dsark1->hide();
            room->hide();
            work15=0;

        });
    });
    //壁画
    dsark2=new designbed(this);

    mypushbutton* sark2=new mypushbutton(":/design/mnjj/design/sark2.png");//
    sark2->setParent(ui->scrollAreaWidgetContents);
    sark2->setIconSize(QSize(300, 200));
    sark2->setFixedSize(300,200);
    //设置气泡
    sark2->setToolTip("柜子");
    sark2->setToolTipDuration(30000);
    sark2->move(0,iconsizeheight*8);//空调
    connect(sark2, &mypushbutton::clicked, [=]() {
        sark2->zoom1();
        sark2->zoom2();
        //延时进入下一个场景
        //qDebug()<<"ssssssss";
        QTimer::singleShot(500,this,[=](){
            //static int work4=1;//只进行一次
            if(work16==1){
                sark2true=new mypushbutton(":/design/mnjj/design/sark2.png");
                copy(this,sark2true,"柜子",dsark2);
                //qDebug()<<"asdasd";
                work16=0;
            }
            if(work16==0){
               sark2true->show();
                work16=2;
            }
        });
    });
    connect(dsark2->cut, &mypushbutton::clicked, [=]() {
        dsark2->cut->zoom1();
        dsark2->cut->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            sark2true->hide();
            dsark2->hide();
            room->hide();
            work16=0;

        });
    });
    //柜子
    dsark3=new designbed(this);

    mypushbutton* sark3=new mypushbutton(":/design/mnjj/design/sark3.png");//
    sark3->setParent(ui->scrollAreaWidgetContents);
    sark3->setIconSize(QSize(300, 200));
    sark3->setFixedSize(300,200);
    //设置气泡
   sark3->setToolTip("柜子");
    sark3->setToolTipDuration(30000);
    sark3->move(iconsizewidth,iconsizeheight*8);//空调
    connect(sark3, &mypushbutton::clicked, [=]() {
        sark3->zoom1();
        sark3->zoom2();
        //延时进入下一个场景
        //qDebug()<<"ssssssss";
        QTimer::singleShot(500,this,[=](){
            //static int work4=1;//只进行一次
            if(work17==1){
                sark3true=new mypushbutton(":/design/mnjj/design/sark3.png");
                copy(this,sark3true,"柜子",dsark3);
                //qDebug()<<"asdasd";
                work17=0;
            }
            if(work17==0){
                sark3true->show();
                work17=2;
            }
        });
    });
    connect(dsark3->cut, &mypushbutton::clicked, [=]() {
        dsark3->cut->zoom1();
        dsark3->cut->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            sark3true->hide();
            dsark3->hide();
            room->hide();
            work17=0;

        });
    });
    //柜子
    dsark4=new designbed(this);

    mypushbutton* sark4=new mypushbutton(":/design/mnjj/design/sark4.png");//
    sark4->setParent(ui->scrollAreaWidgetContents);
    sark4->setIconSize(QSize(300, 200));
    sark4->setFixedSize(300,200);
    //设置气泡
    sark4->setToolTip("柜子");
    sark4->setToolTipDuration(30000);
    sark4->move(0,iconsizeheight*9);//空调
    connect(sark4, &mypushbutton::clicked, [=]() {
        sark4->zoom1();
        sark4->zoom2();
        //延时进入下一个场景
        //qDebug()<<"ssssssss";
        QTimer::singleShot(500,this,[=](){
            //static int work4=1;//只进行一次
            if(work18==1){
                sark4true=new mypushbutton(":/design/mnjj/design/sark4.png");
                copy(this,sark4true,"柜子",dsark4);
                //qDebug()<<"asdasd";
                work18=0;
            }
            if(work18==0){
               sark4true->show();
                work18=2;
            }
        });
    });
    connect(dsark4->cut, &mypushbutton::clicked, [=]() {
        dsark4->cut->zoom1();
        dsark4->cut->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            sark4true->hide();
            dsark4->hide();
            room->hide();
            work18=0;

        });
    });
//shower
    dshower=new designbed(this);

    mypushbutton* shower=new mypushbutton(":/design/mnjj/design/shower.png");//
    shower->setParent(ui->scrollAreaWidgetContents);
    shower->setIconSize(QSize(300, 200));
    shower->setFixedSize(300,200);
    //设置气泡
   shower->setToolTip("花洒");
    shower->setToolTipDuration(30000);
    shower->move(iconsizewidth,iconsizeheight*9);//空调
    connect(shower, &mypushbutton::clicked, [=]() {
       shower->zoom1();
        shower->zoom2();
        //延时进入下一个场景
        //qDebug()<<"ssssssss";
        QTimer::singleShot(500,this,[=](){
            //static int work4=1;//只进行一次
            if(work19==1){
                showertrue=new mypushbutton(":/design/mnjj/design/shower.png");
                copy(this,showertrue,"花洒",dshower);
                //qDebug()<<"asdasd";
                work19=0;
            }
            if(work19==0){
                showertrue->show();
                work19=2;
            }
        });
    });
    connect(dshower->cut, &mypushbutton::clicked, [=]() {
        dshower->cut->zoom1();
        dshower->cut->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            showertrue->hide();
            dshower->hide();
            room->hide();
            work19=0;

        });
    });
    //柜子
    dsofa=new designbed(this);

    mypushbutton* sofa=new mypushbutton(":/design/mnjj/design/sofa.png");//
    sofa->setParent(ui->scrollAreaWidgetContents);
    sofa->setIconSize(QSize(300, 200));
   sofa->setFixedSize(300,200);
    //设置气泡
    sofa->setToolTip("沙发");
    sofa->setToolTipDuration(30000);
    sofa->move(0,iconsizeheight*10);//空调
    connect(sofa, &mypushbutton::clicked, [=]() {
        sofa->zoom1();
        sofa->zoom2();
        //延时进入下一个场景
        //qDebug()<<"ssssssss";
        QTimer::singleShot(500,this,[=](){
            //static int work4=1;//只进行一次
            if(work20==1){
                sofatrue=new mypushbutton(":/design/mnjj/design/sofa.png");
                copy(this,sofatrue,"沙发",dsofa);
                //qDebug()<<"asdasd";
                work20=0;
            }
            if(work20==0){
               sofatrue->show();
                work20=2;
            }
        });
    });
    connect(dsofa->cut, &mypushbutton::clicked, [=]() {
        dsofa->cut->zoom1();
        dsofa->cut->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            sofatrue->hide();
            dsofa->hide();
            room->hide();
            work20=0;
        });
    });
    //shower
        dstool=new designbed(this);

        mypushbutton* stool=new mypushbutton(":/design/mnjj/design/stool.png");//
        stool->setParent(ui->scrollAreaWidgetContents);
        stool->setIconSize(QSize(300, 200));
       stool->setFixedSize(300,200);
        //设置气泡
       stool->setToolTip("马桶");
        stool->setToolTipDuration(30000);
        stool->move(iconsizewidth,iconsizeheight*10);//空调
        connect(stool, &mypushbutton::clicked, [=]() {
           stool->zoom1();
            stool->zoom2();
            //延时进入下一个场景
            //qDebug()<<"ssssssss";
            QTimer::singleShot(500,this,[=](){
                //static int work4=1;//只进行一次
                if(work21==1){
                    stooltrue=new mypushbutton(":/design/mnjj/design/stool.png");
                    copy(this,stooltrue,"马桶",dstool);
                    //qDebug()<<"asdasd";
                    work21=0;
                }
                if(work21==0){
                    stooltrue->show();
                    work21=2;
                }
            });
        });
        connect(dstool->cut, &mypushbutton::clicked, [=]() {
            dstool->cut->zoom1();
            dstool->cut->zoom2();
            //延时进入下一个场景
            QTimer::singleShot(500,this,[=](){
                stooltrue->hide();
                dstool->hide();
                room->hide();
                work21=0;

            });
        });
        //柜子
        dtea=new designbed(this);

        mypushbutton* tea=new mypushbutton(":/design/mnjj/design/tea.png");//
        tea->setParent(ui->scrollAreaWidgetContents);
        tea->setIconSize(QSize(300, 200));
       tea->setFixedSize(300,200);
        //设置气泡
        tea->setToolTip("茶具");
        tea->setToolTipDuration(30000);
        tea->move(0,iconsizeheight*11);//空调
        connect(tea, &mypushbutton::clicked, [=]() {
            tea->zoom1();
            tea->zoom2();
            //延时进入下一个场景
            //qDebug()<<"ssssssss";
            QTimer::singleShot(500,this,[=](){
                //static int work4=1;//只进行一次
                if(work22==1){
                    teatrue=new mypushbutton(":/design/mnjj/design/tea.png");
                    copy(this,teatrue,"茶具",dtea);
                    //qDebug()<<"asdasd";
                    work22=0;
                }
                if(work22==0){
                   teatrue->show();
                    work22=2;
                }
            });
        });
        connect(dtea->cut, &mypushbutton::clicked, [=]() {
            dtea->cut->zoom1();
            dtea->cut->zoom2();
            //延时进入下一个场景
            QTimer::singleShot(500,this,[=](){
                teatrue->hide();
                dtea->hide();
                room->hide();
                work22=0;
            });
        });
        //shower
            dwashbasin=new designbed(this);

            mypushbutton* washbasin=new mypushbutton(":/design/mnjj/design/washbasin.png");//
            washbasin->setParent(ui->scrollAreaWidgetContents);
            washbasin->setIconSize(QSize(300, 200));
           washbasin->setFixedSize(300,200);
            //设置气泡
           washbasin->setToolTip("洗手盆");
            washbasin->setToolTipDuration(30000);
            washbasin->move(iconsizewidth,iconsizeheight*11);//空调
            connect(washbasin, &mypushbutton::clicked, [=]() {
               washbasin->zoom1();
                washbasin->zoom2();
                //延时进入下一个场景
                //qDebug()<<"ssssssss";
                QTimer::singleShot(500,this,[=](){
                    //static int work4=1;//只进行一次
                    if(work23==1){
                       washbasintrue=new mypushbutton(":/design/mnjj/design/washbasin.png");
                        copy(this,washbasintrue,"洗手盆",dwashbasin);
                        //qDebug()<<"asdasd";
                        work23=0;
                    }
                    if(work23==0){
                        washbasintrue->show();
                        work23=2;
                    }
                });
            });
            connect(dwashbasin->cut, &mypushbutton::clicked, [=]() {
                dwashbasin->cut->zoom1();
                dwashbasin->cut->zoom2();
                //延时进入下一个场景
                QTimer::singleShot(500,this,[=](){
                    washbasintrue->hide();
                    dwashbasin->hide();
                    room->hide();
                    work23=0;

                });
            });
            //柜子
            dwashcloth=new designbed(this);
            mypushbutton* washcloth=new mypushbutton(":/design/mnjj/design/washcloth.png");//
            washcloth->setParent(ui->scrollAreaWidgetContents);
            washcloth->setIconSize(QSize(300, 200));
           washcloth->setFixedSize(300,200);
            //设置气泡
            washcloth->setToolTip("毛巾");
            washcloth->setToolTipDuration(30000);
            washcloth->move(0,iconsizeheight*12);//空调
            connect(washcloth, &mypushbutton::clicked, [=]() {
                washcloth->zoom1();
                washcloth->zoom2();
                //延时进入下一个场景
                //qDebug()<<"ssssssss";
                QTimer::singleShot(500,this,[=](){
                    //static int work4=1;//只进行一次
                    if(work24==1){
                        washclothtrue=new mypushbutton(":/design/mnjj/design/washcloth.png");
                        copy(this,washclothtrue,"毛巾",dwashcloth);
                        //qDebug()<<"asdasd";
                        work24=0;
                    }
                    if(work24==0){
                       washclothtrue->show();
                        work24=2;
                    }
                });
            });
            connect(dwashcloth->cut, &mypushbutton::clicked, [=]() {
                dwashcloth->cut->zoom1();
                dwashcloth->cut->zoom2();
                //延时进入下一个场景
                QTimer::singleShot(500,this,[=](){
                    washclothtrue->hide();
                    dwashcloth->hide();
                    room->hide();
                    work24=0;
                });
            });
            //shower
                dwiredesk=new designbed(this);

                mypushbutton* wiredesk=new mypushbutton(":/design/mnjj/design/wiredesk.png");//
                wiredesk->setParent(ui->scrollAreaWidgetContents);
                wiredesk->setIconSize(QSize(300, 200));
               wiredesk->setFixedSize(300,200);
                //设置气泡
               wiredesk->setToolTip("酒柜");
                wiredesk->setToolTipDuration(30000);
                wiredesk->move(iconsizewidth,iconsizeheight*12);//空调
                connect(wiredesk, &mypushbutton::clicked, [=]() {
                   wiredesk->zoom1();
                    wiredesk->zoom2();
                    //延时进入下一个场景
                    //qDebug()<<"ssssssss";
                    QTimer::singleShot(500,this,[=](){
                        //static int work4=1;//只进行一次
                        if(work25==1){
                           wiredesktrue=new mypushbutton(":/design/mnjj/design/wiredesk.png");
                            copy(this,wiredesktrue,"酒柜",dwiredesk);
                            //qDebug()<<"asdasd";
                            work25=0;
                        }
                        if(work25==0){
                            wiredesktrue->show();
                            work25=2;
                        }
                    });
                });
                connect(dwiredesk->cut, &mypushbutton::clicked, [=]() {
                    dwiredesk->cut->zoom1();
                    dwiredesk->cut->zoom2();
                    //延时进入下一个场景
                    QTimer::singleShot(500,this,[=](){
                        wiredesktrue->hide();
                        dwiredesk->hide();
                        room->hide();
                        work25=0;

                    });
                });





}




void designscene::changepicture1(QLineEdit* lineedit,mypushbutton* putton,QLabel* picture,QString stringpix){
    connect(putton, &mypushbutton::clicked, [=]() {
        putton->zoom1();
        putton->zoom2();
        //延时进入下一个场景
        int a=lineedit->text().toInt();//将lineedit的值付给a
        QPixmap pix;
        pix.load(stringpix);//单独的pix.scaled(800,600)没有什么用得在前面加
        pix=pix.scaled(80+10*a,60+10*a);//变化的比例
        picture->setPixmap(pix);
    });
}


void designscene::copy(QWidget* parent,mypushbutton* a,QString tool,QWidget* design){
    //airtrue=new mypushbutton(":/design/mnjj/design/air.png");
    //airtrue->setFixedSize(300,200);
    //airtrue->setIconSize(QSize(300, 200));//设置图标大小
    a->isactive=1;
    a->setParent(parent);
    //设置气泡
    a->setToolTip(tool);
    a->setToolTipDuration(30000);
    a->move(0, 0);//空调
    a->show();
    connect(a,&mypushbutton::clicked,[=](){
        //qDebug()<<"anxiele";
        a->zoom1();
        a->zoom2();
        QTimer::singleShot(500,parent,[=](){
            design->setParent(parent);
            design->setStyleSheet("background-color:#ffffff;"
                                  //"border-radius:5px;"//设置圆角边框
                                  "border:3px solid #abc;"//优化边框（边框有纹路）
                                  );
            design->move(1400,0);//这个才是air设计按钮
            design->show();
        });
    });
    //room->hide();//air显示时room关闭
}
designscene::~designscene()
{
    delete ui;
}
