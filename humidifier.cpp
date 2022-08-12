#include "humidifier.h"
#include "ui_humidifier.h"
#include"QComboBox"
#include"QStandardItemModel"
#include"QStringList"


#include"humimage.h"
QVector<humnum> humnums;
humidifier::humidifier(QWidget *parent,int* a,double* checkmin) :
    QWidget(parent),
    ui(new Ui::humidifier)
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
    ui->lineEdit_8->SetUnitText("RH");


    //确认控件
    ok1=new mypushbutton(":/design/mnjj/design/yes.png");
    ok1->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    ok1->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/yes1.png);}");//background-color:#aaaaaa;
    ok1->setParent(this);
    ok1->move(this->width()*0.4,this->height()-80);
    ok1->setFixedSize(80,60);//80，60规定大小
    ok1->setIconSize(QSize(80,60));

    connect(ok1, &mypushbutton::clicked, [=]() {
        ok1->zoom1();
        ok1->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            this->hide();
            if(ui->comboBox->currentIndex()<4){
                             *a=ui->comboBox->currentIndex();
                *checkmin=ui->lineEdit_8->text().toDouble();

            }

            else{

            }
        });
    });
    //返回控件
    mypushbutton* no=new mypushbutton(":/design/mnjj/design/no.png");
    no->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    no->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    no->setParent(this);//ui->widget在design上面
    no->move(this->width()*0.6,this->height()-80);//按钮的高度与ok1-》height不同 用ok1的数据
    no->setFixedSize(80,60);
    no->setIconSize(QSize(80,60));
    connect(no, &mypushbutton::clicked, [=]() {
        no->zoom1();
        no->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            this->hide();
            if(ui->comboBox->currentIndex()<4){
                             *a=ui->comboBox->currentIndex();
                *checkmin=ui->lineEdit_8->text().toDouble();
            }
            else{

            }
        });
    });
    //删除控件
    cut=new mypushbutton(":/design/mnjj/design/delete.png");
    cut->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    cut->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/delete1.png);background-color:#aaaaaa;}");
    cut->setParent(this);//ui->widget在design上面
    cut->move(this->width()*0.8,this->height()-80);//按钮的高度与ok1-》height不同 用ok1的数据
    cut->setFixedSize(80,60);
    cut->setIconSize(QSize(80,60));
    connect(cut, &mypushbutton::clicked, [=]() {
        cut->zoom1();
        cut->zoom2();
        //延时进入下一个场景
    });

    //设置单位
    ui->lineEdit_4->SetUnitText("db");//功率
    ui->lineEdit_5->SetUnitText("L");//水箱
    ui->lineEdit_6->SetUnitText("ml/h");//加





    combox();
}
void humidifier::combox(){
    //下拉框

    QStringList Items;
    Items.insert(0,"AIRMX秒新——AirWaterA5");
    Items.insert(1,"米家——MJJSQ03DY");
    Items.insert(2,"米家——MJJSQ04DY");
    Items.insert(3,"AIRMX秒新——AirMXAirWaterA3");
    Items.insert(4,"在下面自主设置");

    QStringList Itemstool;//"\n"换行符
    Itemstool.insert(0,"型号：AirWaterA5\n噪声：23db\n水箱容量：7V\n加湿量：1500ml/h");
    Itemstool.insert(1,"型号：MJJSQ03DY\n噪声：34db\n水箱容量：4.5V\n加湿量：450ml/h");
    Itemstool.insert(2,"型号：MJJSQ04DY\n噪声：38db\n水箱容量：4V\n加湿量：300ml/h");
    Itemstool.insert(3,"型号：AirMXAirWaterA3\n噪声：47db\n水箱容量：5V\n加湿量：1200ml/h");
    Itemstool.insert(4,"在下面自主设置");


    humnum humnum1;
    humnum1.sound=23;
    humnum1.waterv=7;
    humnum1.humc=1500;
    humnums.push_back(humnum1);

    humnum1.sound=34;
    humnum1.waterv=4.5;
    humnum1.humc=450;
    humnums.push_back(humnum1);

    humnum1.sound=38;
    humnum1.waterv=4;
    humnum1.humc=300;
    humnums.push_back(humnum1);

    humnum1.sound=47;
    humnum1.waterv=5;
    humnum1.humc=1200;
    humnums.push_back(humnum1);

    QStandardItemModel *model = new QStandardItemModel();//添加提示tootip
    for(int i = 0; i < Items.size(); ++i){
        QStandardItem *item = new QStandardItem(Items.at(i));;
        item->setToolTip(Itemstool.at(i));//设置提示
        model->appendRow(item);

    }

    ui->comboBox->setModel(model);

}
humidifier::~humidifier()
{
    delete ui;
}
