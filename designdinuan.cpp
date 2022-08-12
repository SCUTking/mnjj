#include "designdinuan.h"
#include "ui_designdinuan.h"
#include"QTimer"
#include"QStringList"
#include"QComboBox"
#include"QStandardItemModel"
bool designdinuan::isdinuan=0;//默认是关的
bool designdinuan::isopendinuan=1;//默认是开的，点关闭才是关
int designdinuan::temdinuan=20;//默认升温的温度

designdinuan::designdinuan(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::designdinuan)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    hide();
    ui->widget->setStyleSheet("background-color:#aaaaaa;");//设置嵌入框的颜色
    setStyleSheet("background-color:#ffffff;"
                       "border-radius:5px;"//设置圆角边框
                        "border:3px solid #abc;"//优化边框（边框有纹路）#include"mypushbutton.h" #include"QTimer"

                       );
    ui->widget->setParent(this);

//是否安装地暖
    ifdinuan();
    ui->lineEdit_4->SetUnitText("MW");
    ui->lineEdit_5->SetUnitText("m^2");
    ui->lineEdit_6->SetUnitText("kg");
    ui->lineEdit_7->SetUnitText("度");

//点击地暖按钮后默认安装地暖
    isdinuan=1;



    //确认控件
    ok1=new mypushbutton(":/design/mnjj/design/yes.png");
    ok1->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    ok1->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/yes1.png);background-color:#aaaaaa;}");
    ok1->setParent(this);//ui->widget在design上面
    ok1->move(this->width()*0.4,this->height()-80);//按钮的高度与ok1-》height不同
    ok1->setFixedSize(80,60);
    ok1->setIconSize(QSize(80,60));
    connect(ok1, &mypushbutton::clicked, [=]() {
        ok1->zoom1();
        ok1->zoom2();
        temdinuan=ui->lineEdit_7->text().toInt();//返回温度
        //延时进入下一个场景
        });
    //返回控件
    no=new mypushbutton(":/design/mnjj/design/no.png");
    no->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    no->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    no->setParent(this);//ui->widget在design上面
    no->move(this->width()*0.6,this->height()-80);//按钮的高度与ok1-》height不同
    no->setFixedSize(80,60);
    no->setIconSize(QSize(80,60));
    connect(no, &mypushbutton::clicked, [=]() {
        no->zoom1();
        no->zoom2();
        //延时进入下一个场景
        temdinuan=ui->lineEdit_7->text().toInt();//返回温度
        });



    QStringList Items;
    Items.insert(0,"海尔 L1PB20-HT1");
    Items.insert(1,"史密斯L1PB20-CB");
    Items.insert(2,"史密斯L1PB37-S9");
    Items.insert(3,"在下面自主设置");

    QStringList Itemstool;//"\n"换行符
    Itemstool.insert(0,"额定热功率：0.1MW\n适用面积：50-150m^2\n容水量：14kg");
    Itemstool.insert(1,"额定热功率：0.1MW\n适用面积：0-120m^2\n容水量：13kg");
    Itemstool.insert(2,"额定热功率：0.1MW\n适用面积：160-200m^2\n容水量：12kg");
    Itemstool.insert(3,"在下面自主设置");

    QStandardItemModel *model = new QStandardItemModel();//添加提示tootip
    for(int i = 0; i < Items.size(); ++i){
        QStandardItem *item = new QStandardItem(Items.at(i));;//
        item->setToolTip(Itemstool.at(i));//设置提示
        model->appendRow(item);

    }


    ui->comboBox->setModel(model);

}
void designdinuan::ifdinuan(){




    mypushbutton* open2=new mypushbutton(":/mainscene/mnjj/mainscene/open.png");//,":/mainscene/mnjj/mainscene/close.png"
    open2->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    open2->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no2.png);background-color:#aaaaaa;}");
    open2->setParent(ui->widget);//ui->widget在design上面
    open2->move(250,250);//按钮的高度与ok2-》height不同
    open2->setFixedSize(80,60);
    open2->setIconSize(QSize(80,60));

    mypushbutton* close2=new mypushbutton(":/mainscene/mnjj/mainscene/close.png");//,":/mainscene/mnjj/mainscene/close.png"
    close2->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    close2->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no2.png);background-color:#aaaaaa;}");
    close2->setParent(ui->widget);//ui->widget在design上面
    close2->move(250,250);//按钮的高度与ok2-》height不同
    close2->setFixedSize(80,60);
    close2->setIconSize(QSize(80,60));
    close2->hide();
    connect(close2, &mypushbutton::clicked, [=]() {
        close2->zoom1();
        close2->zoom2();
        isopendinuan=1;

        QTimer::singleShot(500,this,[=](){
            close2->hide();
            open2->show();
            ui->label_18->show();
            ui->lineEdit_7->show();

        });
    });
    connect(open2, &mypushbutton::clicked, [=]() {
        open2->zoom1();
        open2->zoom2();
isopendinuan=0;

        QTimer::singleShot(500,this,[=](){

            open2->hide();
            close2->show();
            ui->label_18->hide();
            ui->lineEdit_7->hide();


        });
    });


    mypushbutton* open1=new mypushbutton(":/mainscene/mnjj/mainscene/open.png");//,":/mainscene/mnjj/mainscene/close.png"
    open1->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    open1->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    open1->setParent(ui->widget);//ui->widget在design上面
    open1->move(250,50);//按钮的高度与ok1-》height不同
    open1->setFixedSize(80,60);
    open1->setIconSize(QSize(80,60));

    mypushbutton* close1=new mypushbutton(":/mainscene/mnjj/mainscene/close.png");//,":/mainscene/mnjj/mainscene/close.png"
    close1->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    close1->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    close1->setParent(ui->widget);//ui->widget在design上面
    close1->move(250,50);//按钮的高度与ok1-》height不同
    close1->setFixedSize(80,60);
    close1->setIconSize(QSize(80,60));
    close1->hide();
    connect(close1, &mypushbutton::clicked, [=]() {
        close1->zoom1();
        close1->zoom2();
        this->isdinuan=1;

        QTimer::singleShot(500,this,[=](){
            close1->hide();
            open1->show();
        open2->show();
            ui->comboBox->show();
            ui->label_17->show();
            ui->label_18->show();
            ui->lineEdit_7->show();

            ui->label_10->show();
            ui->label_13->show();
            ui->widget_2->show();
            ui->widget_3->show();

        });
    });
    connect(open1, &mypushbutton::clicked, [=]() {
        open1->zoom1();
        open1->zoom2();
        this->isdinuan=0;

        QTimer::singleShot(500,this,[=](){
            open2->hide();
            close2->hide();
            open1->hide();
            close1->show();
            ui->comboBox->hide();
            ui->label_17->hide();
            ui->label_18->hide();
            ui->lineEdit_7->hide();

            ui->label_10->hide();
            ui->label_13->hide();
            ui->widget_2->hide();
            ui->widget_3->hide();


        });
    });



}
designdinuan::~designdinuan()
{
    delete ui;
}
