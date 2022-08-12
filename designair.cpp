#include "designair.h"
#include "ui_designair.h"
#include"mytoolbutton.h"
#include"QTimer"

#include"QComboBox"
#include"QStandardItemModel"
#include"QStringList"
#include"temimage.h"
QVector<airnum> airnums;

designair::designair(QWidget *parent,int* a,double* checktem) :
    QWidget(parent),
    ui(new Ui::designair)
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
    ui->lineEdit_11->SetUnitText("度");


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
            *checktem=ui->lineEdit_11->text().toDouble();
            if(ui->comboBox->currentIndex()<6){

                *a=ui->comboBox->currentIndex();//将选择的东西返回

                //temimage::airwhich=ui->comboBox->currentIndex();//将选择的东西传入temimage
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
        *checktem=ui->lineEdit_11->text().toDouble();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
            this->hide();
            *a=ui->comboBox->currentIndex();//将选择的东西返回
            //temimage::airwhich=ui->comboBox->currentIndex();//将选择的东西传入temimage
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
    ui->lineEdit_5->SetUnitText("W");//冷效率
    ui->lineEdit_6->SetUnitText("W");//热量
    ui->lineEdit_7->SetUnitText("W");//热效率
    ui->lineEdit_8->SetUnitText("m^3/h");//循环风量
    ui->lineEdit_9->SetUnitText("匹");//匹数
    ui->lineEdit_10->SetUnitText("级");//能源


    /*ui->play_button->setStyleSheet("QPushButton{border-image: url(:/new/icons/icons/play-pause.png);}"
                              "QPushButton:hover{border-image: url(:/new/icons/icons/play-pause-hover.png);}"
                              "QPushButton:pressed{border-image: url(:/new/icons/icons/play-pause-pressed.png);}");*/
    //下拉框
    combox();

}
void designair::combox(){
    //下拉框

    QStringList Items;
    Items.insert(0,"美的KFR-35GW/BP3DN8Y-");
    Items.insert(1,"美的KFR-35GW/N8MXC1");
    Items.insert(2,"美的KFR-35GW/N8VHC1");
    Items.insert(3,"美的KFR-35GW/N8MXA1");
    Items.insert(4,"美的KFR-26GW/N8VJC");
    Items.insert(5,"美的KFR-35GW/N8MKA1");
    Items.insert(6,"在下面自主设置");

    QStringList Itemstool;//"\n"换行符
    Itemstool.insert(0,"型号：KFR-35GW/BP3DN8Y-\n额定制冷量：3500W\n额定制冷功率：7500W\n额定制热量：5000W\n额定制热功率：1320W\n循环风量：630m^3/h\n匹数：1.5匹\n能耗等级：一级");
    Itemstool.insert(1,"型号：KFR-35GW/N8MXC1\n额定制冷量：3510W\n额定制冷功率：850W\n额定制热量：5010W\n额定制热功率：1270W\n循环风量：750m^3/h\n匹数：1.5匹\n能耗等级：一级");
    Itemstool.insert(2,"型号：KFR-35GW/N8VHC1\n额定制冷量：3500W\n额定制冷功率：750W\n额定制热量：5000W\n额定制热功率：1320W\n循环风量：630m^3/h\n匹数：1.5匹\n能耗等级：一级");
    Itemstool.insert(3,"型号：KFR-35GW/N8MXA1\n额定制冷量：3500W\n额定制冷功率：750W\n额定制热量：5000W\n额定制热功率：1320W\n循环风量：750m^3/h\n匹数：1.5匹\n能耗等级：一级");
    Itemstool.insert(4,"型号：KFR-26GW/N8VJC\n额定制冷量：3900W\n额定制冷功率：645W\n额定制热量：3900W\n额定制热功率：1070W\n循环风量：620m^3/h\n匹数：1.5匹\n能耗等级：一级");
    Itemstool.insert(5,"型号：KFR-35GW/N8MKA1\n额定制冷量：3500W\n额定制冷功率：750W\n额定制热量：5000W\n额定制热功率：1320W\n循环风量：660m^3/h\n匹数：1.5匹\n能耗等级：一级");
    Itemstool.insert(6,"在下面自主设置");

    //将数据载入数组   数据的载入
    airnum airnum1;
    airnum1.icecapacity=3500;
    airnum1.icew=7500;
    airnum1.heatcapacity=5000;
    airnum1.heatw=1320;
    airnum1.airvolume=630;
    airnum1.horse=1.5;
    airnum1.source=1;
    airnums.push_back(airnum1);

    airnum1.icecapacity=3510;
    airnum1.icew=850;
    airnum1.heatcapacity=5010;
    airnum1.heatw=1270;
    airnum1.airvolume=750;
    airnum1.horse=1.5;
    airnum1.source=1;
    airnums.push_back(airnum1);


    airnum1.icecapacity=3500;
    airnum1.icew=750;
    airnum1.heatcapacity=5000;
    airnum1.heatw=1320;
    airnum1.airvolume=630;
    airnum1.horse=1.5;
    airnum1.source=1;
    airnums.push_back(airnum1);


    airnum1.icecapacity=3500;
    airnum1.icew=750;
    airnum1.heatcapacity=5000;
    airnum1.heatw=1320;
    airnum1.airvolume=750;
    airnum1.horse=1.5;
    airnum1.source=1;
    airnums.push_back(airnum1);


    airnum1.icecapacity=3900;
    airnum1.icew=645;
    airnum1.heatcapacity=3900;
    airnum1.heatw=1070;
    airnum1.airvolume=620;
    airnum1.horse=1.5;
    airnum1.source=1;
    airnums.push_back(airnum1);


    airnum1.icecapacity=3500;
    airnum1.icew=750;
    airnum1.heatcapacity=5000;
    airnum1.heatw=1320;
    airnum1.airvolume=660;
    airnum1.horse=1.5;
    airnum1.source=1;
    airnums.push_back(airnum1);






    QStandardItemModel *model = new QStandardItemModel();//添加提示tootip
    for(int i = 0; i < Items.size(); ++i){
        QStandardItem *item = new QStandardItem(Items.at(i));;//
        item->setToolTip(Itemstool.at(i));//设置提示
        model->appendRow(item);

    }


    ui->comboBox->setModel(model);






}
designair::~designair()
{
    delete ui;
}
