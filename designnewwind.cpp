#include "designnewwind.h"
#include "ui_designnewwind.h"
#include"QTimer"
#include"QStringList"
#include"QComboBox"
#include"QStandardItemModel"
bool designnewwind::isnewwind=0;//一开始没有
bool designnewwind::isopennewwind=0;
bool designnewwind::ifchangetem=0;
designnewwind::designnewwind(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::designnewwind)
{
    ui->setupUi(this);

    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    hide();
    ui->widget->setStyleSheet("background-color:#aaaaaa;");//设置嵌入框的颜色
    setStyleSheet("background-color:#aaaaaa;"
                       "border-radius:5px;"//设置圆角边框
                        "border:3px solid #abc;"//优化边框（边框有纹路）#include"mypushbutton.h" #include"QTimer"
                       );
    ui->widget->setParent(this);
    //设置单位为m
    ui->lineEdit->SetUnitText("m");
    ui->lineEdit_2->SetUnitText("m");
    ui->lineEdit_3->SetUnitText("m");

    //安装按钮
    ifnewwind();


    //确认控件
    ok1=new mypushbutton(":/design/mnjj/design/yes.png");
    ok1->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    ok1->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/yes1.png);background-color:#aaaaaa;}");
    ok1->setParent(this);//ui->widget在design上面
    ok1->move(this->width()*0.4,this->height()-80);//按钮的高度与ok1-》height不同
    ok1->setFixedSize(80,60);
    ok1->setIconSize(QSize(80,60));
    connect(ok1, &mypushbutton::clicked, [=]() {
        if(ui->comboBox->currentIndex()==2)
        {
            ifchangetem=1;
        }

        ok1->zoom1();
        ok1->zoom2();
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
        if(ui->comboBox->currentIndex()==2)
        {
            ifchangetem=1;

        }
        no->zoom1();
        no->zoom2();
        //延时进入下一个场景

        });

    ui->comboBox_2->addItem("热交换式");
    ui->comboBox_2->addItem("非热交换式");

    QStringList Items;
    Items.insert(0,"艾泊斯（AirProce）AC");
    Items.insert(1,"松下FY-25ZP1C");
    Items.insert(2,"ArovaneK5");
    Items.insert(3,"在下面自主设置");

    QStringList Itemstool;//"\n"换行符
    Itemstool.insert(0,"最低噪声：22dB\n额定功率：58w\n新风风量：320m^3/h\n热交换");
    Itemstool.insert(1,"最低噪声：27dB\n额定功率：131w\n新风风量：250m^3/h\n热交换");
    Itemstool.insert(2,"最低噪声：26dB\n额定功率：40w\n新风风量：240m^3/h\n非热交换");
    Itemstool.insert(3,"在下面自主设置");

    QStandardItemModel *model = new QStandardItemModel();//添加提示tootip
    for(int i = 0; i < Items.size(); ++i){
        QStandardItem *item = new QStandardItem(Items.at(i));;//
        item->setToolTip(Itemstool.at(i));//设置提示
        model->appendRow(item);

    }


    ui->comboBox->setModel(model);

    ui->lineEdit->SetUnitText("m");
    ui->lineEdit_2->SetUnitText("m");
    ui->lineEdit_3->SetUnitText("m");
    ui->lineEdit_4->SetUnitText("dB");
    ui->lineEdit_5->SetUnitText("w");
    ui->lineEdit_6->SetUnitText("m^3/h");

}
void designnewwind::ifnewwind(){
    mypushbutton* open2=new mypushbutton(":/mainscene/mnjj/mainscene/open.png");//,":/mainscene/mnjj/mainscene/close.png"
    open2->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    open2->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no2.png);background-color:#aaaaaa;}");
    open2->setParent(ui->widget);//ui->widget在design上面
    open2->move(250,240);//按钮的高度与ok2-》height不同
    open2->setFixedSize(80,60);
    open2->setIconSize(QSize(80,60));

    mypushbutton* close2=new mypushbutton(":/mainscene/mnjj/mainscene/close.png");//,":/mainscene/mnjj/mainscene/close.png"
    close2->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    close2->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no2.png);background-color:#aaaaaa;}");
    close2->setParent(ui->widget);//ui->widget在design上面
    close2->move(250,240);//按钮的高度与ok2-》height不同
    close2->setFixedSize(80,60);
    close2->setIconSize(QSize(80,60));
    close2->hide();
    connect(close2, &mypushbutton::clicked, [=]() {
        close2->zoom1();
        close2->zoom2();
        this->isnewwind=2;//打开
        QTimer::singleShot(500,this,[=](){
            close2->hide();
            open2->show();
            isopennewwind=1;
        });
    });
    connect(open2, &mypushbutton::clicked, [=]() {
        open2->zoom1();
        open2->zoom2();
        this->isnewwind=0;//关闭

        QTimer::singleShot(500,this,[=](){

            open2->hide();
            close2->show();

            isopennewwind=0;
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
this->isnewwind=1;//打开
        QTimer::singleShot(500,this,[=](){
            close1->hide();
            open1->show();
            open2->show();
            ui->comboBox->show();
            ui->label->show();
            ui->label_2->show();
            ui->label_6->show();
            ui->label_14->show();
            ui->sizedesign->show();
            ui->label_10->show();
            ui->label_13->show();
            ui->widget_2->show();
            ui->widget_3->show();
            ui->label_16->show();


        });
    });
    connect(open1, &mypushbutton::clicked, [=]() {
        open1->zoom1();
        open1->zoom2();
        this->isnewwind=0;//关闭

        QTimer::singleShot(500,this,[=](){

            open1->hide();
            close2->hide();
            close1->show();
            open2->hide();
            ui->comboBox->hide();
            ui->label->hide();
            ui->label_2->hide();
            ui->label_6->hide();
            ui->label_14->hide();
            ui->sizedesign->hide();
            ui->label_10->hide();
            ui->label_13->hide();
            ui->widget_2->hide();
            ui->widget_3->hide();
            ui->label_16->hide();

        });
    });






}
designnewwind::~designnewwind()
{
    delete ui;
}
