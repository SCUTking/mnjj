#include "choose_city.h"
#include "ui_choose_city.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>//处理cjson数据格式的
#include <QJsonDocument>
#include <QJsonParseError>



#include <QTime>
#include <QDate>
#include <QFile>
#include <QPainter>
#include <QDebug>
#include"QTimer"
int choose_city::tem=0;//初始
int choose_city::hum=0;
int choose_city::pm25=0;
choose_city::choose_city(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::choose_city)
{
ui->setupUi(this);


this->setFixedSize(2000,1200);
this->setWindowTitle("模拟家居环境");


//样式表
ui->widget->setStyleSheet("background-color:#aaaaaa;");//设置嵌入框的颜色
setStyleSheet("background-color:#ffffff;"
              "border-radius:5px;"//设置圆角边框
              "border:3px solid #abc;"//优化边框（边框有纹路）
              );
ui->widget->setParent(this);

//图片载入
QPixmap pix;
pix.load(":/mnjj/allmain/windowicon1.png");//单独的pix.scaled(800,600)没有什么用得在前面加
pix=pix.scaled(100,100);
ui->label_2->setPixmap(pix);

QPixmap pix1;
pix1.load(":/mainscene/mnjj/mainscene/GPS.png");//单独的pix.scaled(800,600)没有什么用得在前面加
pix1=pix1.scaled(100,100);
ui->label_4->setPixmap(pix1);

QPixmap pix2;
pix2.load(":/mainscene/mnjj/mainscene/temicon.png");//单独的pix.scaled(800,600)没有什么用得在前面加
pix2=pix2.scaled(100,100);
ui->label_3->setPixmap(pix2);


QPixmap pix3;
pix3.load(":/mainscene/mnjj/mainscene/humicon.png");//单独的pix.scaled(800,600)没有什么用得在前面加
pix3=pix3.scaled(100,100);
ui->label_12->setPixmap(pix3);

QPixmap pix4;
pix4.load(":/mainscene/mnjj/mainscene/pm.png");//单独的pix.scaled(800,600)没有什么用得在前面加
pix4=pix4.scaled(100,100);
ui->label_13->setPixmap(pix4);





    //确定按钮
    ok1=new mypushbutton(":/design/mnjj/design/yes.png");
    ok1->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    ok1->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/yes1.png);}");//background-color:#aaaaaa;
    ok1->setParent(ui->widget);
    ok1->move(this->width()*0.7,this->height()-80);
    ok1->setFixedSize(80,60);//80，60规定大小
    ok1->setIconSize(QSize(80,60));

    connect(ok1, &mypushbutton::clicked, [=]() {
        ok1->zoom1();
        ok1->zoom2();

        QTimer::singleShot(500,this,[=](){
            //延时进入下一个场景
                        qDebug()<<"到这了1";
            chooseseason=new season;

            this->hide();
            chooseseason->show();
            connect(chooseseason->no, &mypushbutton::clicked, [=]() {
                chooseseason->no->zoom1();
                chooseseason->no->zoom2();
                //延时进入下一个场景
                QTimer::singleShot(500,this,[=](){
                chooseseason->hide();
                this->show();
                });
                });


        });
    });


    no=new mypushbutton(":/design/mnjj/design/no.png");
    no->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    no->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    no->setParent(ui->widget);//ui->widget在design上面
    no->move(this->width()*0.8,this->height()-80);//按钮的高度与ok1-》height不同 用ok1的数据
    no->setFixedSize(80,60);
    no->setIconSize(QSize(80,60));


    //搜索按钮的实现
    mypushbutton* search=new mypushbutton(":/mainscene/mnjj/mainscene/search.png");
    search->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    search->setStyleSheet("QPushButton:hover{border-image: url(:/mainscene/mnjj/mainscene/search.png);}");//background-color:#aaaaaa;
    search->setToolTip("搜索");
    search->setParent(ui->widget);
    search->move(1700,360);
   search->setFixedSize(100,100);//80，60规定大小
    search->setIconSize(QSize(100,100));
    connect(search, &mypushbutton::clicked, [=]() {
        search->zoom1();
        search->zoom2();
        //延时进入下一个场景
        QTimer::singleShot(500,this,[=](){
                on_CheckBt_clicked();
        });
    });





    //显示系统时间
        //启动定时器
        mtime.start();
        //设置定时时间
        mtime.setInterval(1000);
        //将定时器信号与槽函数向关联，每1s执行依次槽函数
        connect(&mtime,SIGNAL(timeout()),this,SLOT(update_time()));

    //获取cJSON数据
        //管理器manager发送报文后就执行槽函数
        connect(&manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(read_cjson(QNetworkReply*)));

        //发送报文
        QUrl url("http://t.weather.itboy.net/api/weather/city/101280101");

        QNetworkRequest request(url);

        manager.get(request);


        //打开文件
        QFile file("citykeys.txt");
        if(!file.open(QIODevice::ReadOnly))
        {
            qDebug()<<"文件打开失败";
        }

        qDebug()<<"文件打开成功";

        QByteArray array;

        while(!file.atEnd())
        {
            QByteArray tmp = file.read(1024);
            //qDebug()<<QString(tmp);
            array.append(tmp);
            //qDebug()<<tmp.size();
        }
        file.close();

        //qDebug()<<QString(array);   //打印不出来,qDebug不能一次性打印太多数据，不然会打印不出来

        QString cityname = array;     //为什么QString可以等于数组
        QStringList citynamelist = cityname.split(",");  //将cityname中得数据分段，按”，“来分成一段一段



        for(int i=0;i<citynamelist.count();i++)
        {
            QString citycn = citynamelist.at(i);
            citycn.remove("\"");

            QStringList idname = citycn.split(":");

            Citys[idname.at(1)] = idname.at(0);
        }









}

choose_city::~choose_city()
{
    delete ui;
}
void choose_city::update_time()
{
    //获取当前系统年月日
    QString System_Date = QDate::currentDate().toString("yyyy-MM-dd");
    ui->DateLcdNumber->display(System_Date);


    //获取当前系统时分秒
    QString System_Time = QTime::currentTime().toString("hh:mm:ss");
    ui->TimeLcdNumber->display(System_Time);

}








void choose_city::read_cjson(QNetworkReply *reply)
{

    QString buf = reply->readAll();    //先把cJOSN数据放入一个缓冲区buf中，定义为字符串类型

    //判断是否为cjson数据
    QJsonParseError err;
                                               //将buf中的数据转换为UTF-8供系统识别
    QJsonDocument doc = QJsonDocument::fromJson(buf.toUtf8(),&err);
    if(err.error != QJsonParseError::NoError)
    {
        qDebug()<<"格式错误";
        return ;
    }

    qDebug()<<"应答CJSON格式正确";              //到了这一步，说明接收回来的cJOSn数据格式是正确的

    QJsonObject obj = doc.object();  //用obj这个量来指向命名cJOSN数据的根，以后要找根目录，就找obj就可以了

    QJsonObject data = obj.value("data").toObject();    //在obj根目录下找到“data”第一子根，用data指向命名

QJsonObject cityinfo = obj.value("cityInfo").toObject();//在obj目录找到cityinfo根

    city = cityinfo.value("city").toString();   //在data第一子根中找到“city”，用city来指向命名
                                            //toString()的作用就是把city中的数据用字符串类型提取出来

    //显示城市
    ui->CityLabel->setText(city);     //将字符串city中的城市信息在ui界面上的Label控件中显示出来

    QJsonArray forecast = data.value("forecast").toArray();  //用一个数组来指向命名“forecase”第二子根

    QJsonObject zero = forecast.at(0).toObject();       //在“forecase”中找到第0号元素

    date = zero.value("date").toString();       //在第0号元素中提示“data”中字符串出来，将日期字符串放在data变量中

    ganmao = data.value("ganmao").toString();



//this->tem=data.value("wendu").toInt();//


    temperature = data.value("wendu").toString();
    this->tem=temperature.toInt();//得先转换成string在转换为int   获取温度
    temperature += "℃";

    //显示温度
    ui->TemperatureLabel->setText(temperature);

    QString humdata = data.value("shidu").toString();
    QString humdatanum=humdata.mid(0,2);//因为humdata带单位，得用截取函数获取，只能时两位数
    this->hum=humdatanum.toInt();//得先转换成string在转换为int   获取湿度
    humdata += "RH";
    //显示湿度
    ui->HumLabel->setText(humdata);


    //该数据比较特殊，不能直接从json变成string
    this->pm25=data.value("pm25").toInt();
    QString pm25data = QString::number(pm25,10);
    //pm25data += "";


    //显示空气污染
    ui->Pm25->setText(pm25data);

}



void choose_city::on_CheckBt_clicked()
{
    QString cityname = ui->InputLineEdit->text();  //获取我们在输入框中的内容
    //加入判断是否为空
    if(cityname==""){

    }
    else{
        qDebug()<<cityname;     //可打印出来，看看我们在输入框输入的城市名字有没有被获取到
        QString cityid = Citys[cityname];//可根据获取到的城市名字得到对应的城市ID
        qDebug()<<"城市id:"<<cityid;

        //QString requesttion = "http://wthrcdn.etouch.cn/weather_mini?citykey=";
        QString requesttion = "http://t.weather.itboy.net/api/weather/city/";
        requesttion += cityid;   //在上面的网址中追加一个城市ID号
        qDebug()<<requesttion;   //可将要发出去的网址信息打印出来看看对不对

        //发送报文
        QUrl url(requesttion);     //当一发送报文，就会产生finished()信号，
                                   //执行read_cjson(QNetworkReply*)函数
                                   //解析CJOSON数据，更新ui界面天气指数信息

        QNetworkRequest request(url);
        manager.get(request);
    }
}



