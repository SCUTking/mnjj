#include "designroom.h"
#include "ui_designroom.h"
#include"mypushbutton.h"
#include"QComboBox"
#include"QStandardItemModel"
#include"QStringList"
#include"QTimer"
QVector<roomnum> roomnums;
designroom::designroom(QWidget *parent,int* a,int* b) :
    QWidget(parent),
    ui(new Ui::designroom)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    hide();
    ui->widget->setStyleSheet("background-color:#aaaaaa;");//设置嵌入框的颜色
    setStyleSheet("background-color:#ffffff;"
                       "border-radius:5px;"//设置圆角边框
                        //"border:3px solid #abc;"//优化边框（边框有纹路）
                       );
    ui->widget->setParent(this);
    //设置单位为m
    ui->lineEdit->SetUnitText("m");
    ui->lineEdit_2->SetUnitText("m");
    ui->lineEdit_3->SetUnitText("m");




    //确认控件
    mypushbutton* ok1=new mypushbutton(":/design/mnjj/design/yes.png");
    ok1->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    ok1->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/yes1.png);background-color:#aaaaaa;}");
    ok1->setParent(this);//ui->widget在design上面
    ok1->move(this->width()*0.5,this->height()-80);//按钮的高度与ok1-》height不同
    ok1->setFixedSize(80,60);
    ok1->setIconSize(QSize(80,60));
    connect(ok1, &mypushbutton::clicked, [=]() {
        ok1->zoom1();
        ok1->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
             this->hide();
            *a=ui->comboBox->currentIndex();
            *b=ui->lineEdit_4->text().toInt();
        });
        });
    //返回控件
    mypushbutton* no=new mypushbutton(":/design/mnjj/design/no.png");
    no->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    no->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    no->setParent(this);//ui->widget在design上面
    no->move(this->width()*0.7,this->height()-80);//按钮的高度与ok1-》height不同
    no->setFixedSize(80,60);
    no->setIconSize(QSize(80,60));
    connect(no, &mypushbutton::clicked, [=]() {
        no->zoom1();
        no->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
             this->hide();

        });
        });

    ui->lineEdit_4->SetUnitText("mm");
    QStringList Items;
    Items.insert(0,"煤矸石多孔砖");
    Items.insert(1,"粘土多孔砖KP1-190");
    Items.insert(2,"灰砂砖240");
    Items.insert(3,"煤矸石烧结砖");


    QStringList Itemstool;//"\n"换行符
    Itemstool.insert(0,"密度：1400kg/m^3\n导热系数:0.54W/(m*k)\n比热容:1051.6J/(kg*k)");
    Itemstool.insert(1,"密度：1400kg/m^3\n导热系数:0.58W/(m*k)\n比热容:1062.3J/(kg*k)");
    Itemstool.insert(2,"密度：1900kg/m^3\n导热系数:1.1W/(m*k)\n比热容:1064.5J/(kg*k)");
    Itemstool.insert(3,"密度：1700kg/m^3\n导热系数:0.63W/(m*k)\n比热容:1051.6J/(kg*k)");




    QStandardItemModel *model = new QStandardItemModel();//添加提示tootip
    for(int i = 0; i < Items.size(); ++i){
        QStandardItem *item = new QStandardItem(Items.at(i));;//
        item->setToolTip(Itemstool.at(i));//设置提示
        model->appendRow(item);

    }
roomnum roomnum1;
roomnum1.heats=0.54;
roomnum1.heatc=1051.6;
roomnums.push_back(roomnum1);

roomnum1.heats=0.58;
roomnum1.heatc=1062.3;
roomnums.push_back(roomnum1);

roomnum1.heats=1.1;
roomnum1.heatc=1064.5;
roomnums.push_back(roomnum1);

roomnum1.heats=0.63;
roomnum1.heatc=1051.6;
roomnums.push_back(roomnum1);

    ui->comboBox->setModel(model);



}

designroom::~designroom()
{
    delete ui;
}
