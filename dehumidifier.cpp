#include "dehumidifier.h"
#include "ui_dehumidifier.h"
#include"QComboBox"
#include"QStandardItemModel"
#include"QStringList"
#include"humimage.h"
QVector<dehumnum> dehumnums;

dehumidifier::dehumidifier(QWidget *parent,int* a,double* checkmax) :
    QWidget(parent),
    ui(new Ui::dehumidifier)
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
    ui->lineEdit_9->SetUnitText("RH");


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
            if(ui->comboBox->currentIndex()<4)
            {
                *a=ui->comboBox->currentIndex();
                *checkmax=ui->lineEdit_9->text().toDouble();
            }

            else{
//
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
            if(ui->comboBox->currentIndex()<4)
            {
                *a=ui->comboBox->currentIndex();
                *checkmax=ui->lineEdit_9->text().toDouble();
            }

            else{
//
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
    ui->lineEdit_4->SetUnitText("W");//冷量
    ui->lineEdit_5->SetUnitText("L");//冷效率
    ui->lineEdit_6->SetUnitText("m^2");//热量
    ui->lineEdit_7->SetUnitText("L/D");//热效率

combox();

}
void dehumidifier::combox(){
    //下拉框

    QStringList Items;
    Items.insert(0,"美的CF12BD/N7-DN");
    Items.insert(1,"美的CF18BD/N7-DF3");
    Items.insert(2,"美的CF20BD/N7-DM200");
    Items.insert(3,"美的CF47BD/N7-DP4");
    Items.insert(4,"在下面自主设置");

    QStringList Itemstool;//"\n"换行符
    Itemstool.insert(0,"型号：CF12BD/N7-DN\n额定功率：239W\n水箱容量：2.1V\n适用面积：40m^2\n除湿量：12L/D");
    Itemstool.insert(1,"型号：CF18BD/N7-DF3\n额定功率：340W\n水箱容量：3V\n适用面积：48m^2\n除湿量：18L/D");
    Itemstool.insert(2,"型号：CF20BD/N7-DM200\n额定功率：315W\n水箱容量：12V\n适用面积：48m^2\n除湿量：20L/D");
    Itemstool.insert(3,"型号：CF47BD/N7-DP4\n额定功率：800W\n水箱容量：7.7V\n适用面积：109m^2\n除湿量：47L/D");
    Itemstool.insert(4,"在下面自主设置");



    dehumnum dehumnum1;
    dehumnum1.w=239;
    dehumnum1.waterv=2.1;
    dehumnum1.size=40;
    dehumnum1.dehumc=12;
    dehumnums.push_back(dehumnum1);

    dehumnum1.w=340;
    dehumnum1.waterv=3;
    dehumnum1.size=48;
    dehumnum1.dehumc=18;
    dehumnums.push_back(dehumnum1);

    dehumnum1.w=315;
    dehumnum1.waterv=12;
    dehumnum1.size=48;
    dehumnum1.dehumc=20;
    dehumnums.push_back(dehumnum1);

    dehumnum1.w=800;
    dehumnum1.waterv=7.7;
    dehumnum1.size=109;
    dehumnum1.dehumc=47;
    dehumnums.push_back(dehumnum1);





    QStandardItemModel *model = new QStandardItemModel();//添加提示tootip
    for(int i = 0; i < Items.size(); ++i){
        QStandardItem *item = new QStandardItem(Items.at(i));;
        item->setToolTip(Itemstool.at(i));//设置提示
        model->appendRow(item);

    }

    ui->comboBox->setModel(model);

}
dehumidifier::~dehumidifier()
{
    delete ui;
}
