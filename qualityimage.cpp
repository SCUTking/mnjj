#include "qualityimage.h"
#include "ui_qualityimage.h"
#include"choose_city.h"
#include <QFile>
#include <QList>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include"QtMath"
#include"ui_humimage.h"
#include"choose_city.h"
static int work300=0;
qualityimage::qualityimage(QWidget *parent,designscene* a,designscene* b,designscene* c,designscene* d) :
    humimage(parent,a,b,c,d)
    //ui(new Ui::qualityimage)
{
ui->setupUi(parent);
startchart();//在这个函数画开始图表的线

qulview=new QLabel(this);

addqulview();//

//setbutton();
//隐藏继承
ui->label_8->hide();
ui->label_9->hide();



//尽管隐藏了chasrtview 但还能用变化的温度和湿度
//点ok1时再画一个图表即可
connect(ok1, &mypushbutton::clicked, [=]() {

    //延时进入下一个场景
    QTimer::singleShot(500,this,[=](){


        initchart();//载入空气质量界面
        if(this->ui->tabWidget->currentIndex()==0){//                                                 whichdesign 一直是0
           //connect(timer,SIGNAL(timeout()),this,SLOT(DrawLine(designk)));
            whichdesign1=0;


        }
        if(this->ui->tabWidget->currentIndex()==1){
            whichdesign1=1;
        }
        if(this->ui->tabWidget->currentIndex()==2){
            whichdesign1=2;

        }
        if(this->ui->tabWidget->currentIndex()==3){
            whichdesign1=3;
        }
        timer = new QTimer;//计时器//创建定时器
        qulview->show();


        chartView->hide();
        qulchartView->show();
        timer->start();//计时器
        timer->setInterval(1000);

         connect(timer,SIGNAL(timeout()),this,SLOT(quldrawline()));
         //connect(timer,SIGNAL(timeout()),this,SLOT(DrawLine()));
    //连接定时器与定时溢出处理槽函数




         work300=0;//多次模拟
    });





});




series->hide();series1->hide();
    /*
    //返回控件
    no=new mypushbutton(":/design/mnjj/design/no.png");
    no->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    no->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    no->setParent(this);//ui->widget在design上面
    no->move(this->width()*0.9,this->height()-80);//按钮的高度与ok1-》height不同
    no->setFixedSize(80,60);
    no->setIconSize(QSize(80,60));*/
    //
    /*setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    hide();
    ui->widget->setStyleSheet("background-color:#aaaaaa;");//设置嵌入框的颜色
    setStyleSheet("background-color:#ffffff;"
                       "border-radius:5px;"//设置圆角边框
                        //"border:3px solid #abc;"//优化边框（边框有纹路）#include"mypushbutton.h" #include"QTimer"

                       );
    ui->widget->setParent(this);



    QLineSeries *lineSeries = new QLineSeries();        //创建折线系列


        QChartView *chartView = new QChartView(this);
        //隐藏背景
        //mChart->setBackgroundVisible(true);
        lineSeries->setName("24小时温度变化");                  //设置线的名称

        lineSeries->setPointLabelsVisible(true);//设置凸点


        mChart = new QChart();                          //创建图标对象


        mChart->addSeries(lineSeries);                  //向图表中添加系列


        //设置x，y的信息和单位
        //setWindowTitle("折线图样例");
        QValueAxis * mAxY = new QValueAxis();
        QValueAxis * mAxX = new QValueAxis();

         //y轴范围
         mAxY->setRange(1, 30);//设置范围

         // Y轴分等份
         mAxY->setTickCount(30);
         mAxX->setRange(1,24);
         mAxX->setTickCount(24);

         // 分辨设置X轴和Y轴的标题
         mAxX->setTitleText(QString(tr("时间/h")));
         mAxY->setTitleText(QString(tr("温度/摄氏度")));



        mChart->addAxis(mAxY, Qt::AlignLeft);
        mChart->addAxis(mAxX, Qt::AlignBottom);
        lineSeries->attachAxis(mAxX);


        lineSeries->attachAxis(mAxY);


        mChart->setTheme(QChart::ChartThemeDark);           //设置图标主题


        mChart->setTitle("温度");                       //设置图标名称



        chartView->setChart(mChart);                    //向chartView中添加图标





        chartView->setRenderHints(QPainter::Antialiasing);//消除边缘，看起来平滑一些

        //为系列里添加100个数据

        for(quint8 i=0; i<25; i++)

        {

            lineSeries->append(i,rand()%30);

        }





        chartView->resize(1400,1200);//设置图表的位置与大小
        chartView->move(0,0);
       //ui->horizontalLayout->addWidget(chartView);     //把chartView放到水平布局中（在ui中拖一个水平布局）




        //确认控件
        mypushbutton* ok1=new mypushbutton(":/design/mnjj/design/yes.png");
        ok1->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
        ok1->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/yes1.png);background-color:#aaaaaa;}");
        ok1->setParent(this);//ui->widget在design上面
        ok1->move(this->width()*0.8,this->height()-80);//按钮的高度与ok1-》height不同
        ok1->setFixedSize(80,60);
        ok1->setIconSize(QSize(80,60));
        connect(ok1, &mypushbutton::clicked, [=]() {
            ok1->zoom1();
            ok1->zoom2();
            //延时进入下一个场景
            QTimer::singleShot(500,this,[=](){

                lineSeries->clear();//清理之前的线
               for(quint8 i=0; i<25; i++)//重新画

               {
                   //lineSeries->append(i,0);

                   lineSeries->append(i,10);

               }

               mChart->addSeries(lineSeries);                  //向图表中添加系列

            });
            });


        //返回控件
        no=new mypushbutton(":/design/mnjj/design/no.png");
        no->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
        no->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
        no->setParent(this);//ui->widget在design上面
        no->move(this->width()*0.9,this->height()-80);//按钮的高度与ok1-》height不同
        no->setFixedSize(80,60);
        no->setIconSize(QSize(80,60));*/
}
void qualityimage::initchart(){
    qulchartView = new QChartView(this);//初始化

    QPen penY(Qt::darkBlue,3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    qulsplinechart = new QChart();
    series2=new QSplineSeries;//直线



    //0画相对湿度   //1画绝对湿度
    axisx2 = new QDateTimeAxis();
    axisy2 = new QValueAxis();
    qulsplinechart->addSeries(series2);                            //把线添加到chart
    axisx2->setTickCount(15);                             //设置坐标轴格数
    axisy2->setTickCount(21);
    axisx2->setFormat("hh:mm:ss");                        //设置时间显示格式
    axisy2->setMin(0);                                    //设置Y轴范围
    axisy2->setMax(100);
    axisx2->setTitleText("模拟设备运行时间");                       //设置X轴名称

    axisy2->setLinePenColor(QColor(Qt::darkBlue));        //设置坐标轴颜色样式
    axisy2->setGridLineColor(QColor(Qt::darkBlue));
    axisy2->setGridLineVisible(false);                    //设置Y轴网格不显示
    axisy2->setLinePen(penY);
    axisy2->setLinePenColor(QColor(Qt::darkBlue));        //设置坐标轴颜色样式
    axisy2->setGridLineColor(QColor(Qt::darkBlue));
    axisy2->setGridLineVisible(false);                    //设置Y轴网格不显示
    axisx2->setLinePen(penY);
    axisy2->setLinePen(penY);


    qulsplinechart->addAxis(axisx2,Qt::AlignBottom);               //设置坐标轴位于chart中的位置
    qulsplinechart->addAxis(axisy2,Qt::AlignLeft);//图表的左边

    qulsplinechart->setTheme(QChart::ChartThemeDark);           //设置图标主题

    series2->attachAxis(axisx2);                           //把数据添加到坐标轴上
    series2->attachAxis(axisy2);
    series2->setName("空气质量分指数");


    axisy2->setTitleText("空气质量分指数");


    //把chart显示到窗口上
    qulchartView->setChart(qulsplinechart);
    qulchartView->setRenderHints(QPainter::Antialiasing);//消除边缘，看起来平滑一些
    qulchartView->resize(1400,1200);//设置图表的位置与大小
    qulchartView->move(0,0);




}
double qualityimage::getqul(int setqul){

    double a=0;
    if(setqul<35){
        return 10*setqul/7;
    }
    else if(setqul<75){
        a=5/4*(setqul-35)+50;
        return a;
    }
    else if(setqul<115){
        a=5/4*(setqul-75)+100;
        return a;
    }


}

void qualityimage::quldrawline(){
    //计算空气质量

    designscene* a=NULL;startend b;
    if(whichdesign1==0){

        a=designk;
        b=startend1;

    }
    if(whichdesign1==1){
        a=designb;
        b=startend2;
    }
    if(whichdesign1==2){
        a=designw;
        b=startend3;

    }
    if(whichdesign1==3){
        a=designl;
        b=startend4;

    }


    double plantde=0.05;\
    double TVde=0.08;
    double airde=0.07;
    double humde=0.04;
    double startqul=qulvector[b.sh];//起始空气质量

    if(work300==0){//只初始化一次
        qul=qulvector[b.sh];
        humtime1=new QDateTime(QDateTime::currentDateTime().date(),QTime(8,0,0,0));//为画线的时间初始化

        work300=1;

    }



    if(a->ifplant==1){
        qul-=plantde;
    }
    if(a->ifTV==1){
        qul+=TVde;
    }
    if(a->openair==1||a->openairtwo){
        qul+=airde;
    }
    if(relhum>80){
        qul+=humde;
    }


    qDebug()<<"qul"<<qul;

    qulview->setText("空气质量："+QString::number(qul));//

    *humtime1=humtime1->addSecs(60);

    qulsplinechart->axisX()->setMin(humtime1->addSecs(-60*15));//画图，这个应该与有多少个间隔来决定
    qulsplinechart->axisX()->setMax(humtime1->addSecs(0));

     series2->append(humtime1->toMSecsSinceEpoch(),qul);



}

/*qualityimage::~qualityimage()
{
    delete
    delete ui;
}*/
void qualityimage::startchart(){

    QLineSeries *lineSeries = new QLineSeries();        //创建折线系列
    //隐藏背景
    //mChart->setBackgroundVisible(true);
    lineSeries->setName("24小时空气质量变化");                  //设置线的名称

    lineSeries->setPointLabelsVisible(true);//设置凸点


    mChart = new QChart();                          //创建图标对象


    mChart->addSeries(lineSeries);                  //向图表中添加系列


    //设置x，y的信息和单位
    //setWindowTitle("折线图样例");
    QValueAxis * mAxY = new QValueAxis();
    QValueAxis * mAxX = new QValueAxis();

    //y轴范围
    mAxY->setRange(0, 100);//设置范围

    // Y轴分等份
    mAxY->setTickCount(25);
    mAxX->setRange(0,24);
    mAxX->setTickCount(25);//设置多少个

    // 分辨设置X轴和Y轴的标题
    mAxX->setTitleText(QString(tr("时间/h")));
    mAxY->setTitleText(QString(tr("空气质量")));



    mChart->addAxis(mAxY, Qt::AlignLeft);
    mChart->addAxis(mAxX, Qt::AlignBottom);
    lineSeries->attachAxis(mAxX);


    lineSeries->attachAxis(mAxY);


    mChart->setTheme(QChart::ChartThemeDark);           //设置图标主题


    mChart->setTitle("空气质量");                       //设置图标名称

    /*为系列里添加100个数据*/
    std::default_random_engine e(time(0));
    std::uniform_real_distribution<double> u1(-3, 4);
    double qulnum=choose_city::pm25;
    for(quint8 i=0; i<25; i++)

    {

        qulvector.push_back(getqul(qulnum)+u1(e));//12temvector[i]//起始温度

    }

    for(quint8 i=0; i<25; i++)

    {

        lineSeries->append(i,qulvector[i]);//12temvector[i]//起始温度

    }
    chartView->setChart(mChart);                    //向chartView中添加图标
    chartView->setRenderHints(QPainter::Antialiasing);//消除边缘，看起来平滑一些
    chartView->resize(1400,1200);//设置图表的位置与大小
    chartView->move(0,0);

}
void qualityimage::addqulview(){//有点麻烦   直接放弃



    qulview->move(1400,this->height()-160);//按钮的高度与ok1-》height不同

    qulview->setFixedSize(250,60);
    QFont font("楷体",18);qulview->setFont(font);
   qulview->setStyleSheet("background-color:#aaaaaa;");//    back->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白



    qulview->hide();






}
void qualityimage::drawpoint(){

    //series2->append(humtime->toMSecsSinceEpoch(),qul);
}
