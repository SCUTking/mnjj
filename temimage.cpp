#include "temimage.h"
#include "ui_temimage.h"
#include"choose_city.h"
#include"QtGlobal"
#include"QTime"
#include"QList"
#include"algorithm"
#include"designnewwind.h"
#include"season.h"
#include"designdinuan.h"
//nt tairwhich=0;
//int temimage::airtwowhich=0;//类内定义类外初始化

static int work60=0;static int work50=0;static int work62=0;//实现多次模拟
static int whichdesign=0;
temimage::temimage(QWidget *parent ,designscene* a,designscene* b,designscene* c,designscene* d) :
    QWidget(parent),
    ui(new Ui::temimage)
{

    ui->setupUi(this);
    //temimage类获取温度 season类

    this->temcount=getseasontem(choose_city::tem);//**********
    //生成温度
    producttemvector();

    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    hide();
    ui->widget->setStyleSheet("background-color:#aaaaaa;");//设置嵌入框的颜色
    setStyleSheet("background-color:#ffffff;"
                  "border-radius:5px;"//设置圆角边框
                  //"border:3px solid #abc;"//优化边框（边框有纹路）#include"mypushbutton.h" #include"QTimer"
                  );
    ui->widget->setParent(this);



    //载入4个设计界面

    designk=a;//将4个design传入temimage
    designl=b;
    designw=c;
    designb=d;


    //tabwidget
    ui->tab->setStyleSheet("background-color:#aaaaaa;"
                           "border-radius:5px;"//设置圆角边框
                           "border:3px solid #abc;"//优化边框（边框有纹路）#include"mypushbutton.h" #include"QTimer"
                           );
    ui->tab_2->setStyleSheet("background-color:#aaaaaa;"
                             "border-radius:5px;"//设置圆角边框
                             "border:3px solid #abc;"//优化边框（边框有纹路）#include"mypushbutton.h" #include"QTimer"
                             );
    ui->tab_3->setStyleSheet("background-color:#aaaaaa;"
                             "border-radius:5px;"//设置圆角边框
                             "border:3px solid #abc;"//优化边框（边框有纹路）#include"mypushbutton.h" #include"QTimer"
                             );
    ui->tab_4->setStyleSheet("background-color:#aaaaaa;"
                             "border-radius:5px;"//设置圆角边框
                             "border:3px solid #abc;"//优化边框（边框有纹路）#include"mypushbutton.h" #include"QTimer"
                             );
    //开关按钮
    setbutton();
    //联动与设计界面
    withdesign();
    //设置单位
    setunit();

    //温度数值
    ui->label_9->hide();
    QFont font1("楷体",18);ui->label_9->setFont(font1);
    ui->label_9->move(1400,890);
    ui->label_9->setStyleSheet("background-color:#aaaaaa;");



    QLineSeries *lineSeries = new QLineSeries();        //创建折线系列


    chartView = new QChartView(this);
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
    mAxY->setRange(0, 38);//设置范围

    // Y轴分等份
    mAxY->setTickCount(38);
    mAxX->setRange(0,24);
    mAxX->setTickCount(25);//设置多少个

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

    /*为系列里添加100个数据*/

    for(quint8 i=0; i<25; i++)

    {

        lineSeries->append(i,temvector[i]);//12temvector[i]//起始温度

    }





    chartView->resize(1400,1200);//设置图表的位置与大小
    chartView->move(0,0);



    //ui->horizontalLayout->addWidget(chartView);     //把chartView放到水平布局中（在ui中拖一个水平布局）
    //曲线图



    //splineChart=new QChart();

    //mChart->axes(Qt::Horizontal).first()->setRange(0, 9);
    // mChart->axes(Qt::Vertical).first()->setRange(0, 20);
    /*QSplineSeries *series1 = new QSplineSeries(mChart);
         series1->setName("温度变化曲线");
        //series1 << QPointF(0,10) << QPointF(2,7) << QPointF(3,9) << QPointF(8,13) << QPointF(9,16);
        for(int i=0;i<25;i++){
            series1->append(i,temvector[i]-5);
        }
        mChart->addSeries(series1);*/





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



            ui->label_9->show();
            gettime();//获取数据
            mChart->hide();
            initDraw();//载入曲线图

            //实现多次摸拟
            work60=0;
            work50=0;

            //开关按钮
            setbutton();
            //联动与设计界面
            withdesign();


            //设置单位
            setunit();

            //void(temimage:: *signal1)(designscene*)=&temimage::toDrawline;



            if(ui->tabWidget->currentIndex()==0){
                //connect(timer,SIGNAL(timeout()),this,SLOT(DrawLine(designk)));
                whichdesign=0;
                checktem(temcount,designk);//只有一开始根据平均温度判断 是否打开空调
            }
            if(ui->tabWidget->currentIndex()==1){
                whichdesign=1;
                checktem(temcount,designb);

            }
            if(ui->tabWidget->currentIndex()==2){
                whichdesign=2;
                checktem(temcount,designw);

            }
            if(ui->tabWidget->currentIndex()==3){
                whichdesign=3;
                checktem(temcount,designl);

            }

            timer = new QTimer;//计时器//创建定时器
            connect(timer,SIGNAL(timeout()),this,SLOT(DrawLine()));
            //连接定时器与定时溢出处理槽函数
            timer->start();//计时器
            timer->setInterval(1000);
            /*lineSeries->clear();//清理之前的线
               for(quint8 i=0; i<25; i++)//重新画

               {
                   //lineSeries->append(i,0);

                   //lineSeries->append(i,designb->airtwowhich);

               }*/

            //mChart->addSeries(lineSeries);                  //向图表中添加系列

        });
    });


    //返回控件
    no=new mypushbutton(":/design/mnjj/design/no.png");
    no->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    no->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    no->setParent(this);//ui->widget在design上面
    no->move(this->width()*0.9,this->height()-80);//按钮的高度与ok1-》height不同
    no->setFixedSize(80,60);
    no->setIconSize(QSize(80,60));

}

void temimage::checktem(double tem,designscene *a){
if(a->ifair==1){
    if(tem>checktemnum){
        if(whichdesign==0){
        open1->show();
        close1->hide();
        a->openair=1;
        }
        if(whichdesign==1){
            open3->show();
            close3->hide();
            a->openair=1;

        }
        if(whichdesign==2){
            open5->show();
            close5->hide();
            a->openair=1;

        }
        if(whichdesign==3){
            open7->show();
            close7->hide();
            a->openair=1;

        }
    }

}


if(a->ifairtwo==1){
    if(tem>checktemnum)
    {
        if(whichdesign==0){
        open2->show();
        close2->hide();
        a->openairtwo=1;

        }
        if(whichdesign==1){
            open4->show();
            close4->hide();
            a->openairtwo=1;

        }
        if(whichdesign==2){
            open6->show();
            close6->hide();
            a->openairtwo=1;

        }
        if(whichdesign==3){
            open8->show();
            close8->hide();
            a->openairtwo=1;

        }
    }

}




}

int temimage::getseasontem(int citytem){
    int changeeachseason=5;
    if(season::whichseason==0){//春季
        return citytem-changeeachseason*2;
    }
    if(season::whichseason==1){//夏季
        return citytem;
    }
    if(season::whichseason==2){//秋季
        return citytem-changeeachseason*2;
    }
    if(season::whichseason==3){//冬季
        return citytem-changeeachseason*4;
    }
}

double rand_back(double i,double j) { //生成正太分布的随机数据
    double u1=double(rand()%1000)/1000,u2=double(rand()%1000)/1000,r;
    //static unsigned int seed=0;
    r=i+sqrt(j)*sqrt(-2.0*(log(u1)/log(exp(1.0))))*cos(2*pi*u2);
    return r;
}
//房间设置对温度影响
double temimage::productsimulate(airnum a,designscene *b,double in,double out){
    int windV=a.airvolume;//循环风量
    double daore=b->roomk.heats;//导热系数
    double s=b->rooms;//墙的面积
    double wallwidth=b->roomwidth;//墙的厚度
    double Qchange=daore*s*(out-in)/wallwidth;//外界热传导进入房间的温度（傅里叶热传导公式）


    double icew=(a.icecapacity-productreduce(b)-Qchange)*0.8598;//制冷量 单位转换 减去消耗量
    double temchange=icew/(k*Cp*windV*60);//每过1分钟变化的温度
    return temchange;

}
double temimage::productreduce(designscene *a){
    int eachwindowreduce=150;
    double reduce=a->ifwindow*eachwindowreduce;//窗体对制冷量的损耗
    return reduce;
}
void temimage::producttemvector(){
    int shu=10;
    srand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i=0;i<25;i++){
        temvector.push_back(shu);
    }
    int sunrise=6;//没有也说有
    int sundown=18;

    for (int i = 0; i < 6; i++) {
        temvector[i]=rand_back(temcount-3, 1);
    }
    QVector<double> a;
    srand( (unsigned)time( NULL ) );
    for (int i = 6; i <= 14; i++) {
        a.push_back(rand_back(temcount,3.0));
        std::sort(a.begin(),a.end());

    }


    //QList<double>::iterator it;  //构建一个list容器的迭代器it
    for(int i=0;i<a.size();i++){
        temvector[i+6]=a[i];
    }

    for (int i = 15; i <= 24; i++) {
        if(i==15||i==16){
            temvector[15]=temvector[14]-3;
            temvector[16]=temvector[15]-2;
        }
        else{
            temvector[i]=rand_back(temcount-3, 1);

        }
    }



}
temimage::~temimage()
{
    delete ui;
}
void temimage::initDraw()
{
    QPen penY(Qt::darkBlue,3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    splinechart = new QChart();
    series = new QSplineSeries;
    series1=new QSplineSeries;//直线
    axisX = new QDateTimeAxis();
    axisY = new QValueAxis();

    //splinechart->legend()->hide();                             //隐藏图例
    splinechart->addSeries(series);                            //把线添加到chart
    splinechart->addSeries(series1);
    axisX->setTickCount(15);                             //设置坐标轴格数
    axisY->setTickCount(38);
    axisX->setFormat("hh:mm:ss");                        //设置时间显示格式
    axisY->setMin(0);                                    //设置Y轴范围
    axisY->setMax(38);
    axisX->setTitleText("模拟空调运行时间");                       //设置X轴名称
    axisY->setLinePenColor(QColor(Qt::darkBlue));        //设置坐标轴颜色样式
    axisY->setGridLineColor(QColor(Qt::darkBlue));
    axisY->setGridLineVisible(false);                    //设置Y轴网格不显示
    axisY->setLinePen(penY);
    axisX->setLinePen(penY);

    splinechart->addAxis(axisX,Qt::AlignBottom);               //设置坐标轴位于chart中的位置
    splinechart->addAxis(axisY,Qt::AlignLeft);
    splinechart->setTheme(QChart::ChartThemeDark);           //设置图标主题

    series->attachAxis(axisX);                           //把数据添加到坐标轴上
    series->attachAxis(axisY);
    series1->attachAxis(axisX);                           //把数据添加到坐标轴上
    series1->attachAxis(axisY);
    series1->setName("空调预设温度");
    series->setName("室内实际温度");


    axisY->setTitleText("温度/摄氏度");

    //把chart显示到窗口上
    chartView->setChart(splinechart);
    //ui->widget->setChart(chart);
    //ui->widget->setRenderHint(QPainter::Antialiasing);   //设置抗锯齿
}
void temimage::DrawLine()
{



    designscene* a=NULL;startend b;
    if(whichdesign==0){
        a=designk;
        b=startend1;
    }
    if(whichdesign==1){
        a=designb;
        b=startend2;
    }
    if(whichdesign==2){
        a=designw;
        b=startend3;
    }
    if(whichdesign==3){
        a=designl;
        b=startend4;
    }
    static double refreshtem;static double number;static double risetem;static double goaltem;
    int refreshtime=10;
    QTime starttime=QTime(b.sh,b.smin,0,0);
    QTime endtime=QTime(b.eh,b.emin,0,0);

    if(work50==0){//只初始化一次
        airtime=new QDateTime(QDateTime::currentDateTime().date(),QTime(starttime.hour(),starttime.minute(),0,0));
        number =temvector[starttime.hour()];
        refreshtem=b.tem;//应该是运行的最后一次温度无法获取
         goaltem=designdinuan::temdinuan;
         risetem=temvector[starttime.hour()];
        work50=1;
    }    //QTime mintime=airtime.addSecs(0);
    //QTime maxtime=airtime.addSecs(60);
    //QDateTime currentTime = QDateTime::currentDateTime();
    //设置坐标轴显示范围***************************************************************
    //splinechart->axisX()->setMin(QDateTime::currentDateTime().addSecs(-60 * 1));       //系统当前时间的前一秒
    //splinechart->axisX()->setMax(QDateTime::currentDateTime().addSecs(0));            //系统当前时间
    //splinechart->axisX()->setMax();
    //number为实时室内温度 而temvector[airtime->time().hour()为实时外界温度

    double change=productsimulate(a->airk,a,number,temvector[airtime->time().hour()]);//生成改变量
    double changenewwind;
    if(designnewwind::isnewwind&&designnewwind::isopennewwind&&designnewwind::ifchangetem){//判断新风是否打开
        changenewwind=productnewwind(number,temvector[airtime->time().hour()],a);
    }
    else{
        changenewwind=0;
    }
    //qDebug()<<changenewwind;

    splinechart->axisX()->setMin(airtime->addSecs(-60*15));//画图，这个应该与有多少个间隔来决定
    splinechart->axisX()->setMax(airtime->addSecs(0));
    //判断空调是否开
    if((a->ifair!=0&&a->openair!=0)||(a->ifairtwo!=0&&a->openairtwo!=0)){
        if(endtime<airtime->time()){//回温设置
            if(refreshtem>temvector[endtime.hour()]){
                *airtime=airtime->addSecs(0);
            }
            else{

                double eachlengthtem=(temvector[endtime.hour()]-b.tem)/refreshtime;//使用空调结束运行时的外界温度


                refreshtem+=eachlengthtem;

                ui->label_9->setText("温度："+QString::number(refreshtem));//

                series->append(airtime->toMSecsSinceEpoch(),refreshtem);
                series1->append(airtime->toMSecsSinceEpoch(),b.tem);


            }


        }
        else{
            *airtime=airtime->addSecs(60 * 1);//每隔30分钟画一个点                        //这里生成随机数做测试
            std::default_random_engine e(time(0));
            std::uniform_real_distribution<double> u(-0.12, 0.12);
            //增加新的点到曲线末端
            ui->label_9->setText("温度："+QString::number(number));//

            series->append(airtime->toMSecsSinceEpoch(),number);
            series1->append(airtime->toMSecsSinceEpoch(),b.tem);
            if(number<b.tem){//变频设置
                work60=1;
                number+=u(e);
            }
            else{
                if(work60==0){
                    if(changenewwind<change)
                    number-=(change+u(e)-changenewwind);
                    else
                        number-=(change+u(e));
                }
                else{
                    number-=u(e);
                }
            }


        }
    }
    //当安装地暖且打开后
    else if(designdinuan::isopendinuan&&designdinuan::isdinuan){//地暖升温
       //开始温度//
        *airtime=airtime->addSecs(60);

        std::default_random_engine e(time(0));
        std::uniform_real_distribution<double> u(-0.12, 0.12);
        //增加新的点到曲线末端
        ui->label_9->setText("温度："+QString::number(risetem));//

        series->append(airtime->toMSecsSinceEpoch(),risetem);
        series1->append(airtime->toMSecsSinceEpoch(),goaltem);
        if(risetem>goaltem){//变频设置
            work62=1;
            risetem-=u(e);
        }
        else{
            if(work62==0){
                    risetem+=(change+0.08);
                    qDebug()<<change;
            }
            else{
                risetem-=u(e);
            }
        }

    }
    else{
        //不开空调时为外界温度       不开地暖
        ui->label_9->setText("温度："+QString::number(temvector[airtime->time().hour()]));//

        *airtime=airtime->addSecs(60);
        series->append(airtime->toMSecsSinceEpoch(),temvector[airtime->time().hour()]);

    }


}
void temimage::setunit(){

    ui->lineEdit->SetUnitText("度");
    ui->lineEdit_6->SetUnitText("度");
    ui->lineEdit_11->SetUnitText("度");
    ui->lineEdit_42->SetUnitText("度");
    ui->lineEdit_43->SetUnitText("度");
    ui->lineEdit_20->SetUnitText("度");
    ui->lineEdit_25->SetUnitText("度");
    ui->lineEdit_44->SetUnitText("度");

    ui->lineEdit->setMaxLength(2);
    ui->lineEdit_11->setMaxLength(2);
    ui->lineEdit_20->setMaxLength(2);
    ui->lineEdit_25->setMaxLength(2);
    ui->lineEdit_43->setMaxLength(2);
    ui->lineEdit_44->setMaxLength(2);
    ui->lineEdit_42->setMaxLength(2);
    ui->lineEdit_6->setMaxLength(2);

    ui->lineEdit_2->SetUnitText("时");
    ui->lineEdit_3->SetUnitText("分");
    ui->lineEdit_4->SetUnitText("时");
    ui->lineEdit_5->SetUnitText("分");

    ui->lineEdit_12->SetUnitText("时");
    ui->lineEdit_13->SetUnitText("分");
    ui->lineEdit_14->SetUnitText("时");
    ui->lineEdit_15->SetUnitText("分");

    ui->lineEdit_21->SetUnitText("时");
    ui->lineEdit_22->SetUnitText("分");
    ui->lineEdit_23->SetUnitText("时");
    ui->lineEdit_24->SetUnitText("分");

    ui->lineEdit_16->SetUnitText("时");
    ui->lineEdit_17->SetUnitText("分");
    ui->lineEdit_18->SetUnitText("时");
    ui->lineEdit_19->SetUnitText("分");

    ui->lineEdit_30->SetUnitText("时");
    ui->lineEdit_31->SetUnitText("分");
    ui->lineEdit_32->SetUnitText("时");
    ui->lineEdit_33->SetUnitText("分");

    ui->lineEdit_34->SetUnitText("时");
    ui->lineEdit_35->SetUnitText("分");
    ui->lineEdit_36->SetUnitText("时");
    ui->lineEdit_37->SetUnitText("分");

    ui->lineEdit_38->SetUnitText("时");
    ui->lineEdit_39->SetUnitText("分");
    ui->lineEdit_40->SetUnitText("时");
    ui->lineEdit_41->SetUnitText("分");

    ui->lineEdit_26->SetUnitText("时");
    ui->lineEdit_27->SetUnitText("分");
    ui->lineEdit_28->SetUnitText("时");
    ui->lineEdit_29->SetUnitText("分");

}
void temimage::gettime(){
    if(openair1){

        if(ui->lineEdit_2->text().toInt()==0&&ui->lineEdit_3->text().toInt()==0&&ui->lineEdit_4->text().toInt()==0&&ui->lineEdit_5->text().toInt()==0){

        }
        else{
            if(startend1.sh<=startend1.eh){
                startend1.sh=ui->lineEdit_2->text().toInt();
                startend1.smin=ui->lineEdit_3->text().toInt();
                startend1.eh=ui->lineEdit_4->text().toInt();
                startend1.emin=ui->lineEdit_5->text().toInt();
            }
        }
    }


    if(ui->lineEdit->text().toInt()!=0)
        startend1.tem=ui->lineEdit->text().toInt();

    if(openair2){
        if(ui->lineEdit_12->text().toInt()==0&&ui->lineEdit_13->text().toInt()==0&&ui->lineEdit_14->text().toInt()==0&&ui->lineEdit_15->text().toInt()==0){

        }
        else{
            if(startend2.sh<=startend2.eh){
                startend2.sh=ui->lineEdit_12->text().toInt();
                startend2.smin=ui->lineEdit_13->text().toInt();
                startend2.eh=ui->lineEdit_14->text().toInt();
                startend2.emin=ui->lineEdit_15->text().toInt();
            }}
    }

    if(ui->lineEdit_11->text().toInt()!=0)
        startend2.tem=ui->lineEdit_11->text().toInt();

    if(openair3){
        if(ui->lineEdit_16->text().toInt()==0&&ui->lineEdit_17->text().toInt()==0&&ui->lineEdit_18->text().toInt()==0&&ui->lineEdit_19->text().toInt()==0){

        }
        else{
            if(startend3.sh<=startend3.eh){
                startend3.sh=ui->lineEdit_16->text().toInt();
                startend3.smin=ui->lineEdit_17->text().toInt();
                startend3.eh=ui->lineEdit_18->text().toInt();
                startend3.emin=ui->lineEdit_19->text().toInt();
            }}
    }
    if(ui->lineEdit_20->text().toInt()!=0)
        startend3.tem=ui->lineEdit_20->text().toInt();

    if(openair4){
        if(ui->lineEdit_21->text().toInt()==0&&ui->lineEdit_22->text().toInt()==0&&ui->lineEdit_23->text().toInt()==0&&ui->lineEdit_24->text().toInt()==0){

        }
        else{
            if(startend4.sh<=startend4.eh){
                startend4.sh=ui->lineEdit_21->text().toInt();
                startend4.smin=ui->lineEdit_22->text().toInt();
                startend4.eh=ui->lineEdit_23->text().toInt();
                startend4.emin=ui->lineEdit_24->text().toInt();
            }}
    }
    if(ui->lineEdit_25->text().toInt()!=0)
        startend4.tem=ui->lineEdit_25->text().toInt();
}

void temimage::withdesign(){
    if(designk->ifair==0){
        ui->label->hide();
        open1->hide();
        ui->lineEdit->hide();
        ui->widget_4->hide();
        ui->widget_2->hide();

    }
    if(designk->ifairtwo==0){
        ui->label_3->hide();
        open2->hide();
        ui->lineEdit_6->hide();
        ui->widget_3->hide();
        ui->widget_20->hide();
    }

    if(designb->ifair==0){
        ui->label_17->hide();
        open3->hide();
        ui->lineEdit_11->hide();
        ui->widget_9->hide();
        ui->widget_10->hide();

    }
    if(designb->ifairtwo==0){
        ui->label_19->hide();
        open4->hide();
        ui->lineEdit_42->hide();
        ui->widget_8->hide();
        ui->widget_18->hide();
    }
    if(designw->ifair==0){
        ui->label_26->hide();
        open5->hide();
        ui->lineEdit_20->hide();
        ui->widget_12->hide();
        ui->widget_13->hide();

    }
    if(designw->ifairtwo==0){
        ui->label_28->hide();
        open6->hide();
        ui->lineEdit_43->hide();
        ui->widget_11->hide();
        ui->widget_17->hide();
    }
    if(designl->ifair==0){
        ui->label_33->hide();
        open7->hide();
        ui->lineEdit_25->hide();
        ui->widget_15->hide();
        ui->widget_16->hide();

    }
    if(designl->ifairtwo==0){
        ui->label_35->hide();
        open8->hide();
        ui->lineEdit_44->hide();
        ui->widget_14->hide();
        ui->widget_19->hide();
    }

}
void temimage::setbutton(){

    open1=new mypushbutton(":/mainscene/mnjj/mainscene/open.png");//,":/mainscene/mnjj/mainscene/close.png"
    open1->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    open1->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    open1->setParent(ui->tab);//ui->widget在design上面
    open1->move(200,0);//按钮的高度与ok1-》height不同
    open1->setFixedSize(80,60);
    open1->setIconSize(QSize(80,60));

    close1=new mypushbutton(":/mainscene/mnjj/mainscene/close.png");//,":/mainscene/mnjj/mainscene/close.png"
    close1->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    close1->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    close1->setParent(ui->tab);//ui->widget在design上面
    close1->move(200,0);//按钮的高度与ok1-》height不同
    close1->setFixedSize(80,60);
    close1->setIconSize(QSize(80,60));
    close1->hide();
    connect(close1, &mypushbutton::clicked, [=]() {
        close1->zoom1();
        close1->zoom2();
        openair1=1;
        if(openair1)
        {
            designk->openair=1;
        }
        QTimer::singleShot(500,this,[=](){
            ui->lineEdit->show();
            ui->widget_4->show();
            ui->widget_2->show();
            close1->hide();
            open1->show();
        });
    });
    connect(open1, &mypushbutton::clicked, [=]() {
        open1->zoom1();
        open1->zoom2();
        openair1=0;
        if(openair1==0)
        {
            designk->openair=0;
        }
        QTimer::singleShot(500,this,[=](){
            ui->lineEdit->hide();
            ui->widget_4->hide();
            ui->widget_2->hide();
            open1->hide();
            close1->show();
        });
    });

    open2=new mypushbutton(":/mainscene/mnjj/mainscene/open.png");//,":/mainscene/mnjj/mainscene/close.png"
    open2->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    open2->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    open2->setParent(ui->tab);//ui->widget在design上面
    open2->move(200,300);//按钮的高度与ok1-》height不同
    open2->setFixedSize(80,60);
    open2->setIconSize(QSize(80,60));

    close2=new mypushbutton(":/mainscene/mnjj/mainscene/close.png");//,":/mainscene/mnjj/mainscene/close.png"
    close2->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    close2->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    close2->setParent(ui->tab);//ui->widget在design上面
    close2->move(200,300);//按钮的高度与ok1-》height不同
    close2->setFixedSize(80,60);
    close2->setIconSize(QSize(80,60));
    close2->hide();
    connect(close2, &mypushbutton::clicked, [=]() {
        close2->zoom1();
        close2->zoom2();
        openairtwo1=1;
        if(openairtwo1){
            designk->openairtwo=1;
        }
        QTimer::singleShot(500,this,[=](){
            ui->lineEdit_6->show();
            ui->widget_3->show();
            ui->widget_20->show();
            close2->hide();
            open2->show();
        });
    });
    connect(open2, &mypushbutton::clicked, [=]() {
        open2->zoom1();
        open2->zoom2();
        openairtwo1=0;
        if(openairtwo1==0){
            designk->openairtwo=0;
        }
        QTimer::singleShot(500,this,[=](){
            ui->lineEdit_6->hide();
            ui->widget_3->hide();
            ui->widget_20->hide();
            open2->hide();
            close2->show();
        });
    });

    open3=new mypushbutton(":/mainscene/mnjj/mainscene/open.png");//,":/mainscene/mnjj/mainscene/close.png"
    open3->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    open3->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    open3->setParent(ui->tab_2);//ui->widget在design上面
    open3->move(200,0);//按钮的高度与ok1-》height不同
    open3->setFixedSize(80,60);
    open3->setIconSize(QSize(80,60));

    close3=new mypushbutton(":/mainscene/mnjj/mainscene/close.png");//,":/mainscene/mnjj/mainscene/close.png"
    close3->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    close3->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    close3->setParent(ui->tab_2);//ui->widget在design上面
    close3->move(200,0);//按钮的高度与ok1-》height不同
    close3->setFixedSize(80,60);
    close3->setIconSize(QSize(80,60));
    close3->hide();
    connect(close3, &mypushbutton::clicked, [=]() {
        close3->zoom1();
        close3->zoom2();
        openair2=1;
        designb->openair=1;
        QTimer::singleShot(500,this,[=](){
            ui->lineEdit_11->show();
            ui->widget_9->show();
            ui->widget_10->show();
            close3->hide();
            open3->show();
        });
    });
    connect(open3, &mypushbutton::clicked, [=]() {
        open3->zoom1();
        open3->zoom2();
        openair2=0;
        designb->openair=0;
        QTimer::singleShot(500,this,[=](){
            ui->lineEdit_11->hide();
            ui->widget_9->hide();
            ui->widget_10->hide();
            open3->hide();
            close3->show();
        });
    });

    open4=new mypushbutton(":/mainscene/mnjj/mainscene/open.png");//,":/mainscene/mnjj/mainscene/close.png"
    open4->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    open4->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    open4->setParent(ui->tab_2);//ui->widget在design上面
    open4->move(200,300);//按钮的高度与ok1-》height不同
    open4->setFixedSize(80,60);
    open4->setIconSize(QSize(80,60));

    close4=new mypushbutton(":/mainscene/mnjj/mainscene/close.png");//,":/mainscene/mnjj/mainscene/close.png"
    close4->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    close4->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    close4->setParent(ui->tab_2);//ui->widget在design上面
    close4->move(200,300);//按钮的高度与ok1-》height不同
    close4->setFixedSize(80,60);
    close4->setIconSize(QSize(80,60));
    close4->hide();
    connect(close4, &mypushbutton::clicked, [=]() {
        close4->zoom1();
        close4->zoom2();
        openairtwo2=1;
        designb->openairtwo=1;
        QTimer::singleShot(500,this,[=](){
            ui->lineEdit_42->show();
            ui->widget_8->show();
            ui->widget_18->show();
            close4->hide();
            open4->show();
        });
    });
    connect(open4, &mypushbutton::clicked, [=]() {
        open4->zoom1();
        open4->zoom2();
        openairtwo2=0;
        designb->openairtwo=0;
        QTimer::singleShot(500,this,[=](){
            ui->lineEdit_42->hide();
            ui->widget_8->hide();
            ui->widget_18->hide();
            open4->hide();
            close4->show();
        });
    });


    open5=new mypushbutton(":/mainscene/mnjj/mainscene/open.png");//,":/mainscene/mnjj/mainscene/close.png"
    open5->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    open5->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    open5->setParent(ui->tab_3);//ui->widget在design上面
    open5->move(200,0);//按钮的高度与ok1-》height不同
    open5->setFixedSize(80,60);
    open5->setIconSize(QSize(80,60));

    close5=new mypushbutton(":/mainscene/mnjj/mainscene/close.png");//,":/mainscene/mnjj/mainscene/close.png"
    close5->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    close5->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    close5->setParent(ui->tab_3);//ui->widget在design上面
    close5->move(200,0);//按钮的高度与ok1-》height不同
    close5->setFixedSize(80,60);
    close5->setIconSize(QSize(80,60));
    close5->hide();
    connect(close5, &mypushbutton::clicked, [=]() {
        close5->zoom1();
        close5->zoom2();
        openair3=1;
        designw->openair=1;
        QTimer::singleShot(500,this,[=](){
            ui->lineEdit_20->show();
            ui->widget_12->show();
            ui->widget_13->show();
            close5->hide();
            open5->show();
        });
    });
    connect(open5, &mypushbutton::clicked, [=]() {
        open5->zoom1();
        open5->zoom2();
        openair3=0;
        designw->openair=0;
        QTimer::singleShot(500,this,[=](){
            ui->lineEdit_20->hide();
            ui->widget_12->hide();
            ui->widget_13->hide();
            open5->hide();
            close5->show();
        });
    });


    open6=new mypushbutton(":/mainscene/mnjj/mainscene/open.png");//,":/mainscene/mnjj/mainscene/close.png"
    open6->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    open6->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    open6->setParent(ui->tab_3);//ui->widget在design上面
    open6->move(200,300);//按钮的高度与ok1-》height不同
    open6->setFixedSize(80,60);
    open6->setIconSize(QSize(80,60));

    close6=new mypushbutton(":/mainscene/mnjj/mainscene/close.png");//,":/mainscene/mnjj/mainscene/close.png"
    close6->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    close6->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    close6->setParent(ui->tab_3);//ui->widget在design上面
    close6->move(200,300);//按钮的高度与ok1-》height不同
    close6->setFixedSize(80,60);
    close6->setIconSize(QSize(80,60));
    close6->hide();
    connect(close6, &mypushbutton::clicked, [=]() {
        close6->zoom1();
        close6->zoom2();
        openairtwo3=1;
        designw->openairtwo=1;
        QTimer::singleShot(500,this,[=](){
            ui->lineEdit_43->show();
            ui->widget_11->show();
            ui->widget_17->show();
            close6->hide();
            open6->show();
        });
    });
    connect(open6, &mypushbutton::clicked, [=]() {
        open6->zoom1();
        open6->zoom2();
        openairtwo3=0;
        designw->openairtwo=0;
        QTimer::singleShot(500,this,[=](){
            ui->lineEdit_43->hide();
            ui->widget_11->hide();
            ui->widget_17->hide();
            open6->hide();
            close6->show();
        });
    });


    open7=new mypushbutton(":/mainscene/mnjj/mainscene/open.png");//,":/mainscene/mnjj/mainscene/close.png"
    open7->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    open7->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    open7->setParent(ui->tab_4);//ui->widget在design上面
    open7->move(200,0);//按钮的高度与ok1-》height不同
    open7->setFixedSize(80,60);
    open7->setIconSize(QSize(80,60));

    close7=new mypushbutton(":/mainscene/mnjj/mainscene/close.png");//,":/mainscene/mnjj/mainscene/close.png"
    close7->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    close7->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    close7->setParent(ui->tab_4);//ui->widget在design上面
    close7->move(200,0);//按钮的高度与ok1-》height不同
    close7->setFixedSize(80,60);
    close7->setIconSize(QSize(80,60));
    close7->hide();
    connect(close7, &mypushbutton::clicked, [=]() {
        close7->zoom1();
        close7->zoom2();
        openair4=1;
        designl->openair=1;
        QTimer::singleShot(500,this,[=](){
            ui->lineEdit_25->show();
            ui->widget_15->show();
            ui->widget_16->show();
            close7->hide();
            open7->show();
        });
    });
    connect(open7, &mypushbutton::clicked, [=]() {
        open7->zoom1();
        open7->zoom2();
        openair4=0;
        designl->openair=0;
        QTimer::singleShot(500,this,[=](){
            ui->lineEdit_25->hide();
            ui->widget_15->hide();
            ui->widget_16->hide();
            open7->hide();
            close7->show();
        });
    });

    open8=new mypushbutton(":/mainscene/mnjj/mainscene/open.png");//,":/mainscene/mnjj/mainscene/close.png"
    open8->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    open8->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    open8->setParent(ui->tab_4);//ui->widget在design上面
    open8->move(200,300);//按钮的高度与ok1-》height不同
    open8->setFixedSize(80,60);
    open8->setIconSize(QSize(80,60));

    close8=new mypushbutton(":/mainscene/mnjj/mainscene/close.png");//,":/mainscene/mnjj/mainscene/close.png"
    close8->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    close8->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    close8->setParent(ui->tab_4);//ui->widget在design上面
    close8->move(200,300);//按钮的高度与ok1-》height不同
    close8->setFixedSize(80,60);
    close8->setIconSize(QSize(80,60));
    close8->hide();
    connect(close8, &mypushbutton::clicked, [=]() {
        close8->zoom1();
        close8->zoom2();
        openairtwo4=1;
        designl->openairtwo=1;
        QTimer::singleShot(500,this,[=](){
            ui->lineEdit_44->show();
            ui->widget_14->show();
            ui->widget_19->show();
            close8->hide();
            open8->show();
        });
    });
    connect(open8, &mypushbutton::clicked, [=]() {
        open8->zoom1();
        open8->zoom2();
        openairtwo4=0;
        designl->openairtwo=0;
        QTimer::singleShot(500,this,[=](){
            ui->lineEdit_44->hide();
            ui->widget_14->hide();
            ui->widget_19->hide();
            open8->hide();
            close8->show();
        });
    });



}
double temimage::productnewwind(double intotem,double outtem,designscene* a){
    int eachmintinuewind=4;
    double rate=eachmintinuewind/a->roomv;//比例送风量与房间的体积
    double iotem=outtem-intotem;//夏季
    double temchange=iotem*rate;
    return temchange*0.1;//设置系数不然太离谱
}
