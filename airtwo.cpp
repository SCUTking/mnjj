#include "airtwo.h"
#include "ui_airtwo.h"
#include"QTimer"
#include"QComboBox"
#include"QStandardItemModel"
#include"QStringList"

#include"temimage.h"

QVector<airtwonum> airtwonums;
airtwo::airtwo(QWidget *parent,int* a) :
    QWidget(parent),
    ui(new Ui::airtwo)
{
    ui->setupUi(this);
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
            if(ui->comboBox->currentIndex()<6){

                *a=ui->comboBox->currentIndex();
                //temimage::des=ui->comboBox->currentIndex();//将选择的东西传入temimage
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
    //
    combox();
}
void airtwo::combox(){
    //下拉框

    QStringList Items;
    Items.insert(0,"美的KFR-72LW/N8VHC1");
    Items.insert(1,"美的KFR-72LW/N8HF3");
    Items.insert(2,"美的KFR-72LW/N8MJC3");
    Items.insert(3,"美的KFR-51LW/N8MJC3");
    Items.insert(4,"美的KFR-72LW/N8MFA3");
    Items.insert(5,"美的KFR-51LW/N8MJA3");
    Items.insert(6,"在下面自主设置");

    QStringList Itemstool;//"\n"换行符
    Itemstool.insert(0,"型号：KFR-72LW/N8VHC1\n额定制冷量：7210W\n额定制冷功率：1970W\n额定制热量：9660W\n额定制热功率：2950W\n循环风量：1300m^3/h\n匹数：3匹\n能耗等级：一级");
    Itemstool.insert(1,"型号：KFR-72LW/N8HF3\n额定制冷量：7200W\n额定制冷功率：2800W\n额定制热量：9200W\n额定制热功率：3159W\n循环风量：1300m^3/h\n匹数：3匹\n能耗等级：一级");
    Itemstool.insert(2,"型号：KFR-72LW/N8MJC3\n额定制冷量：7290W\n额定制冷功率：2700W\n额定制热量：9410W\n额定制热功率：3150W\n循环风量：1300m^3/h\n匹数：3匹\n能耗等级：一级");
    Itemstool.insert(3,"型号：KFR-51LW/N8MJC3\n额定制冷量：5120W\n额定制冷功率：1560W\n额定制热量：7160W\n额定制热功率：2050W\n循环风量：1020m^3/h\n匹数：2匹\n能耗等级：一级");
    Itemstool.insert(4,"型号：KFR-72LW/N8MFA3\n额定制冷量：7200W\n额定制冷功率：2350W\n额定制热量：9100W\n额定制热功率：2800W\n循环风量：1200m^3/h\n匹数：2匹\n能耗等级：一级");
    Itemstool.insert(5,"型号：KFR-51LW/N8MJA3\n额定制冷量：5100W\n额定制冷功率：1610W\n额定制热量：7100W\n额定制热功率：2200W\n循环风量：1000m^3/h\n匹数：2匹\n能耗等级：一级");
    Itemstool.insert(6,"在下面自主设置");

    //将数据载入数组   数据的载入
    airtwonum airtwonum1;

    airtwonum1.icecapacity=7210;
    airtwonum1.icew=1970;
    airtwonum1.heatcapacity=9660;
    airtwonum1.heatw=2950;
    airtwonum1.airvolume=1300;
    airtwonum1.horse=3;
    airtwonum1.source=1;
    airtwonums.push_back(airtwonum1);

    airtwonum1.icecapacity=7200;
    airtwonum1.icew=2800;
    airtwonum1.heatcapacity=9200;
    airtwonum1.heatw=3159;
    airtwonum1.airvolume=1300;
    airtwonum1.horse=3;
    airtwonum1.source=1;
    airtwonums.push_back(airtwonum1);

    airtwonum1.icecapacity=7290;
    airtwonum1.icew=2700;
    airtwonum1.heatcapacity=9410;
    airtwonum1.heatw=3150;
    airtwonum1.airvolume=1300;
    airtwonum1.horse=3;
    airtwonum1.source=1;
    airtwonums.push_back(airtwonum1);

    airtwonum1.icecapacity=5120;
    airtwonum1.icew=1560;
    airtwonum1.heatcapacity=7160;
    airtwonum1.heatw=2050;
    airtwonum1.airvolume=1020;
    airtwonum1.horse=2;
    airtwonum1.source=1;
    airtwonums.push_back(airtwonum1);

    airtwonum1.icecapacity=7200;
    airtwonum1.icew=2350;
    airtwonum1.heatcapacity=9100;
    airtwonum1.heatw=2800;
    airtwonum1.airvolume=1200;
    airtwonum1.horse=2;
    airtwonum1.source=1;
    airtwonums.push_back(airtwonum1);

    airtwonum1.icecapacity=5100;
    airtwonum1.icew=1610;
    airtwonum1.heatcapacity=7100;
    airtwonum1.heatw=2200;
    airtwonum1.airvolume=1000;
    airtwonum1.horse=2;
    airtwonum1.source=1;
    airtwonums.push_back(airtwonum1);








    QStandardItemModel *model = new QStandardItemModel();//添加提示tootip
    for(int i = 0; i < Items.size(); ++i){
        QStandardItem *item = new QStandardItem(Items.at(i));;//
        item->setToolTip(Itemstool.at(i));//设置提示
        model->appendRow(item);

    }


    ui->comboBox->setModel(model);






}
airtwo::~airtwo()
{
    delete ui;
}
