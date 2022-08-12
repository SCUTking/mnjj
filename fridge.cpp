#include "fridge.h"
#include "ui_fridge.h"
#include"QTimer"
#include"QComboBox"
#include"QStandardItemModel"
#include"QStringList"

QVector<fridgenum> fridgenums;



frigde::frigde(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frigde)
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
    ui->lineEdit_4->SetUnitText("kg/12h");//
    ui->lineEdit_5->SetUnitText("L");//冷效率
    ui->lineEdit_6->SetUnitText("级");//热量

//
    combox();


}
void frigde::combox(){
    //下拉框

    QStringList Items;
    Items.insert(0,"美的BCD-606WKPZM€");
    Items.insert(1,"美的BCD-601WKPZM€");
    Items.insert(2,"美的BCD-478WSPZM€");
    Items.insert(3,"美的BCD-470WKPZM€");
    Items.insert(4,"美的BCD-600WKGPZM€");
    Items.insert(5,"美的BCD-603WKGPZM(Q)");
    Items.insert(6,"在下面自主设置");

    QStringList Itemstool;//"\n"换行符
    Itemstool.insert(0,"型号：BCD-606WKPZM€\n总容积：606L\n冷冻能力：6kg/12h\n能耗等级：一级\n耗电量：0.95度/天");
    Itemstool.insert(1,"型号：BCD-601WKPZM€\n总容积：601L\n冷冻能力：8kg/12h\n能耗等级：一级\n耗电量：0.88度/天");
    Itemstool.insert(2,"型号：BCD-478WSPZM€\n总容积：478L\n冷冻能力：6kg/12h\n能耗等级：一级\n耗电量：0.85度/天");
    Itemstool.insert(3,"型号：BCD-470WKPZM€\n总容积：470L\n冷冻能力：6kg/12h\n能耗等级：一级\n耗电量：0.81度/天");
    Itemstool.insert(4,"型号：BCD-600WKGPZM€\n总容积：600L\n冷冻能力：8kg/12h\n能耗等级：一级\n耗电量：0.88度/天");
    Itemstool.insert(5,"型号：BCD-603WKGPZM(Q)\n总容积：603L\n冷冻能力：8kg/12h\n能耗等级：一级\n耗电量：0.88度/天");
    Itemstool.insert(6,"在下面自主设置");

    //将数据载入数组   数据的载入
    fridgenum fridge1;
    fridge1.ice=6;
    fridge1.source=1;
    fridge1.v=606;
    fridgenums.push_back(fridge1);

    fridge1.ice=8;
    fridge1.source=1;
    fridge1.v=601;
    fridgenums.push_back(fridge1);

    fridge1.ice=6;
    fridge1.source=1;
    fridge1.v=478;
    fridgenums.push_back(fridge1);

    fridge1.ice=6;
    fridge1.source=1;
    fridge1.v=470;
    fridgenums.push_back(fridge1);

    fridge1.ice=8;
    fridge1.source=1;
    fridge1.v=600;
    fridgenums.push_back(fridge1);

    fridge1.ice=8;
    fridge1.source=1;
    fridge1.v=603;
    fridgenums.push_back(fridge1);





    QStandardItemModel *model = new QStandardItemModel();//添加提示tootip
    for(int i = 0; i < Items.size(); ++i){
        QStandardItem *item = new QStandardItem(Items.at(i));;//
        item->setToolTip(Itemstool.at(i));//设置提示
        model->appendRow(item);

    }


    ui->comboBox->setModel(model);






}
frigde::~frigde()
{
    delete ui;
}
