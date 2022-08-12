#include "humimage.h"
#include "ui_humimage.h"
#include"choose_city.h"
#include <QFile>
#include <QList>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include"QtMath"
int work61=0;
int work51=0;//实现多次模拟
//int whichdesign1=0;

int changehum=0;
int work100=0;//温度停止时湿度也停止
humimage::humimage(QWidget *parent ,designscene* a,designscene* b,designscene* c,designscene* d) :
    QWidget(parent),
    ui(new Ui::humimage)
{
    ui->setupUi(this);
    //temimage类获取温度
    this->temcount=getseasontem(choose_city::tem);//**********
    //temimage类获取湿度
    this->humcount=getseasonhum(choose_city::hum);
qDebug()<<choose_city::hum;
    //获取绝对和相对湿度初始值

ui->label_8->hide();
QFont font("楷体",18);ui->label_8->setFont(font);
ui->label_8->move(1400,800);
ui->label_8->setStyleSheet("background-color:#aaaaaa;");


ui->label_9->hide();
QFont font1("楷体",18);ui->label_9->setFont(font1);
ui->label_9->move(1400,890);
ui->label_9->setStyleSheet("background-color:#aaaaaa;");

    //生成温度
    producttemvector();
    //生成湿度
    producthumvector();
    //创造相对湿度和绝对湿度vector
    loadhum();

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

 chartView = new QChartView(this);
    startchart();

    //提到上面初始化 使得qulimage类能够隐藏
    series = new QSplineSeries;
    series1=new QSplineSeries;//直线












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
     ok1=new mypushbutton(":/design/mnjj/design/yes.png");
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

            ui->label_8->show();
            ui->label_9->show();


            gettime();//获取数据
            mChart->hide();
            initDraw();//载入曲线图

            //实现多次摸拟
            work61=0;
            work51=0;
            changehum=0;


            //开关按钮
            setbutton();
            //联动与设计界面
            withdesign();


            //设置单位
            setunit();

        //void(temimage:: *signal1)(designscene*)=&temimage::toDrawline;



            if(ui->tabWidget->currentIndex()==0){
               //connect(timer,SIGNAL(timeout()),this,SLOT(DrawLine(designk)));
                whichdesign1=0;
                this->checkmax=designk->checkmax;
                this->checkmin=designk->checkmin;
            }
            if(ui->tabWidget->currentIndex()==1){
                whichdesign1=1;
                this->checkmax=designb->checkmax;
                this->checkmin=designb->checkmin;
            }
            if(ui->tabWidget->currentIndex()==2){
                whichdesign1=2;
                this->checkmax=designw->checkmax;
                this->checkmin=designw->checkmin;
            }
            if(ui->tabWidget->currentIndex()==3){
                whichdesign1=3;
                this->checkmax=designl->checkmax;
                this->checkmin=designl->checkmin;
            }
            qDebug()<<this->checkmax;
            qDebug()<<this->checkmin;

            timer = new QTimer;//计时器//创建定时器
             connect(timer,SIGNAL(timeout()),this,SLOT(getpoint()));
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

void humimage::startchart(){
    QLineSeries *lineSeries = new QLineSeries();        //创建折线系列
    //隐藏背景
    //mChart->setBackgroundVisible(true);
    lineSeries->setName("24小时湿度变化");                  //设置线的名称

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
    mAxY->setTitleText(QString(tr("湿度")));



    mChart->addAxis(mAxY, Qt::AlignLeft);
    mChart->addAxis(mAxX, Qt::AlignBottom);
    lineSeries->attachAxis(mAxX);


    lineSeries->attachAxis(mAxY);


    mChart->setTheme(QChart::ChartThemeDark);           //设置图标主题


    mChart->setTitle("湿度");                       //设置图标名称

    /*为系列里添加100个数据*/

    for(quint8 i=0; i<25; i++)

    {

        lineSeries->append(i,humvector[i]);//12temvector[i]//起始温度

    }


    chartView->setChart(mChart);                    //向chartView中添加图标

    chartView->setRenderHints(QPainter::Antialiasing);//消除边缘，看起来平滑一些
    chartView->resize(1400,1200);//设置图表的位置与大小
    chartView->move(0,0);

}

void humimage::BPhum(double tem,double hum){

//int layer=3;        //三层神经网络
//int NUM=10;       //每层的最多节点数
double w[3][10][10];    //BP网络的权值
double b[3][10];         //BP网络节点的阀值
double x[3][10];         //每个神经元的值经S型函数转化后的输出值，输入层就为原值
double temp[12];double temp1[6];

//初始化
memset(w, 0, sizeof(w));      //初始化权值和阀值为0，也可以初始化随机值
memset(x, 0, sizeof(x));
//memset(p, 0, sizeof(p));
for(int i=0;i<6;i++){
    p.push_back(0);
}


int hd_num=6;
int ou_num=1;//只有一个输出
int in_num=2;//两个输入

x[0][0]=tem;x[0][1]=hum;//输入
qDebug()<<"输入"<<tem<<" "<<hum;



//获取权值和阀值
QFile file("E:/vs/fun/hide.txt");
if(!file.open(QIODevice::ReadOnly))
{
    qDebug()<<"文件打开失败";
}

int i=0;
while(file.atEnd() == false)//文件没到末尾就执行循环体内容
{
    QByteArray buf = file.readLine();//读取一行的数据
    temp[i]=buf.toDouble();

    i++;
}
    for(int i=0;i<6;i++){
        w[1][0][i]=temp[i];

    }
    for(int i=0;i<6;i++){
        w[1][1][i]=temp[i+6];

    }
file.close();//关闭文件

//输出的权值
QFile file1("E:/vs/fun/out.txt");
if(!file1.open(QIODevice::ReadOnly))
{
    qDebug()<<"文件打开失败";
}

int g=0;
int j=0;
while(file1.atEnd() == false)//文件没到末尾就执行循环体内容
{
        QByteArray buf = file1.readLine();//读取一行的数据
        temp1[j]=buf.toDouble();
        j++;
}
for(int g=0;g<6;g++){
    w[2][g][0]=temp1[g];//g为隐含
}


file1.close();//关闭文件



//计算隐含层各个节点的输出值
for (int j = 0; j < hd_num; j++)
{
    p[j]=0;
    for (int i = 0; i < in_num; i++)//输入2个
    {
        p[j] += w[1][i][j] * x[0][j];//输入乘以权值
    }

    p[j] += b[1][j];//加上阀值
    qDebug()<<"p"<<p[j];
    x[1][j] = sigmoid(p[j]);//用函数输出



    qDebug()<<"x[0][j] "<<x[0][j] ;
    qDebug()<<"x[1][j] "<<x[1][j] ;

}

//计算输出层各节点的输出值
for (int j = 0; j < ou_num; j++)
{
    double t = 0;
    for (int i = 0; i < hd_num; i++)//输出1个
    {
        t += w[2][i][j] * x[1][i];//将隐含层累加到一个  //输出只有一个 w相当于2维
    }
    t += b[2][j];
    x[2][j] = sigmoid(t);
    relhum=(x[2][j]-0.3)*100;//输出计数结果  *10///***********************************************
}



}
double humimage::sigmoid(double x){
    //A和B是S型函数的参数
    double a=30;
    double b=10;
    if(qIsNaN(a / (1 + exp(-x / b))))
    {
        return 0;
    }
    else{
           return a / (1 + exp(-x / b));
    }

}
int humimage::whichtem(double a){//这个函数没有用
    for(int i=0;i<8;i++){
        if(a<=(i+1)*5){
            return i;//第几个温度
        }
    }
}
int humimage::whichrelhum(double b,int a){
    for(int i=0;i<20;i++){
        if(b<hum[a][i]){
            return i;//第几个湿度
        }
        if(i==19){
            return i;
        }
    }
}
double humimage::whichabshum(int b,int a)//这个函数没有用
{
    for(int i=0;i<20;i++){
        if(b<5*(i+1)){
            return hum[a][i];
        }
    }
}
void humimage::changedata(designscene* a,startend b){

    //随机性
    std::default_random_engine e(time(0));
    std::uniform_real_distribution<double> u1(-0.12, 0.12);
    //改变绝对湿度
    if(changehum==0){
        //设置为absnum上限为96，看上去比较合理
        if(a->opendehum&&abshum>=1&&abshum<=96&&a->ifdehum){
            double eachdehum=a->dehumk.dehumc*1000/(24*60);//换算公式
            abshum=(abshum*a->roomv-eachdehum*3)/a->roomv;


        }
        if(a->openhum&&abshum<=96&&a->ifhum){
            double eachhum=a->humk.humc/(60);
            abshum=(abshum*a->roomv+eachhum)/a->roomv;
        }
        //打开一个就改变  改变相对湿度
        int whichtemnum=whichtem(simatetem);//
        relhum=whichrelhum(abshum,whichtemnum)*5+5+u1(e);
        //BPhum(simatetem,abshum);//参数为模拟温度 和绝对湿度
        qDebug()<<relhum;
        qDebug()<<simatetem;

        //relhum=whichrelhum(abshum,whichtemnum)*5+5;//获取相对湿度//////////////////////////////////////////////////////修改这里
    }

    //人体最佳的湿度范围
    if(relhum<=50&&relhum>40)///40<x<=50
    {
        changehum=1;
        int whichtemnum=whichtem(simatetem);//参数为模拟温度
        relhum=whichrelhum(abshum,whichtemnum)*5+5+u1(e);
        abshum+=u1(e);
        //BPhum(simatetem,abshum);
        qDebug()<<relhum;

    }
    else{
        changehum=0;//当由于温度改变使得湿度改变时，除湿器开始工作
    }
}
int humimage::getseasontem(int citytem){
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
int humimage::getseasonhum(int cityhum){
    int changeeachseason=5;
    if(season::whichseason==0){//春季
        return cityhum;
    }
    if(season::whichseason==1){//夏季
        return cityhum;
    }
    if(season::whichseason==2){//秋季
        return cityhum-changeeachseason*2;
    }
    if(season::whichseason==3){//冬季
        return cityhum-changeeachseason*2;
    }
}
void humimage::checkhum(double relhum,designscene* a){
    if(a->ifhum){
        if(relhum<checkmin){
            if(ui->tabWidget->currentIndex()==0){
                designk->openhum=1;//打开
                open9->show();
                close9->close();
            }
            if(ui->tabWidget->currentIndex()==1){
                designb->openhum=1;//打开

                open11->show();
                close11->close();
            }
            if(ui->tabWidget->currentIndex()==2){
                designw->openhum=1;//打开

                open13->show();
                close13->close();
            }
            if(ui->tabWidget->currentIndex()==3){
                designl->openhum=1;//打开

                open15->show();
                close15->close();
            }
        }
        else if(relhum>checkmax) {//等到relhum>checkmax
            //加斯器关闭
            open9->close();
            open11->close();
            open15->close();
            open13->close();
            //参数关闭
            designk->openhum=0;
            designb->openhum=0;
            designw->openhum=0;
            designl->openhum=0;

            //asdas
            close9->show();
            close11->show();
            close13->show();
            close15->show();
        }
    }

}
void humimage::checkdehum(double relhum,designscene* a){
    if(a->ifdehum==1){
        if(relhum>checkmax){
            if(ui->tabWidget->currentIndex()==0){
                designk->opendehum=1;//打开

                open10->show();
                close10->close();
            }
            if(ui->tabWidget->currentIndex()==1){
                designb->opendehum=1;//打开

                open12->show();
                close12->close();
            }
            if(ui->tabWidget->currentIndex()==2){
                designw->opendehum=1;//打开

                open14->show();
                close14->close();
            }
            if(ui->tabWidget->currentIndex()==3){
                designl->opendehum=1;//打开

                open16->show();
                close16->close();
            }
        }
        else if(relhum<checkmax) {//等到relhum>checkmax
            //加斯器关闭
            open10->close();
            open12->close();
            open14->close();
            open16->close();


            designk->opendehum=0;//打开
            designb->opendehum=0;//打开
            designw->opendehum=0;//打开
            designl->opendehum=0;//打开

            //asdas
            close10->show();
            close12->show();
            close14->show();
            close16->show();
        }
    }

}
void humimage::DrawLine()
{


//在getpoint函数那获取了relhum和开始时间
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
    //改变数据
    changedata(a,b);
  //检查加湿器和除湿器
    checkhum(relhum,a);
    checkdehum(relhum,a);



    splinechart->axisX()->setMin(humtime->addSecs(-60*15));//画图，这个应该与有多少个间隔来决定
    splinechart->axisX()->setMax(humtime->addSecs(0));
if(work100==0){
    *humtime=humtime->addSecs(60);
    ui->label_8->setText("相对湿度："+QString::number(relhum));//
    ui->label_9->setText("绝对湿度："+QString::number(abshum));//
}



    series->append(humtime->toMSecsSinceEpoch(),relhum);
    series1->append(humtime->toMSecsSinceEpoch(),abshum);
}
void humimage::producthumvector(){
    int shu=30;
    //初始画
    for(int i=0;i<25;i++){
        humvector.push_back(shu);
    }

    int sunrise=6;
    int sundown=18;
    //0到9正太分布随机
    /*    for (int i = 0; i < 10; i++) {
        humvector[i]=rand_back(humcount, 1);
    }
    for (int i = 10; i <= 17; i++) {
        humvector[i]=rand_back(humcount-5-i*0.7, 1);
    }
    for (int i = 18; i <= 24; i++) {
        humvector[i]=rand_back(humcount-15+i*0.3, 1);
    }*/
    for (int i = 0; i < 10; i++) {
        humvector[i]=rand_back(humcount+15-i*2.3, 1);
    }
    for (int i = 10; i <= 17; i++) {
        humvector[i]=rand_back(humcount, 1);
    }
    for (int i = 18; i <= 24; i++) {
        humvector[i]=rand_back(humcount+i*0.6, 3);
    }

}
void humimage::initDraw()
{
    QPen penY(Qt::darkBlue,3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    splinechart = new QChart();

    //0画相对湿度   //1画绝对湿度
    axisX = new QDateTimeAxis();
    axisY = new QValueAxis();
    axisY1=new QValueAxis();

    //splinechart->legend()->;                             //隐藏图例
    splinechart->addSeries(series);                            //把线添加到chart
    splinechart->addSeries(series1);
    axisX->setTickCount(15);                             //设置坐标轴格数
    axisY->setTickCount(38);
    axisY1->setTickCount(38);
    axisX->setFormat("hh:mm:ss");                        //设置时间显示格式
    axisY->setMin(0);                                    //设置Y轴范围
    axisY->setMax(100);
    axisY1->setMin(0);                                    //设置Y轴范围
    axisY1->setMax(55);
    axisX->setTitleText("模拟设备运行时间");                       //设置X轴名称

    axisY->setLinePenColor(QColor(Qt::darkBlue));        //设置坐标轴颜色样式
    axisY->setGridLineColor(QColor(Qt::darkBlue));
    axisY->setGridLineVisible(false);                    //设置Y轴网格不显示
    axisY->setLinePen(penY);
    axisY1->setLinePenColor(QColor(Qt::darkBlue));        //设置坐标轴颜色样式
    axisY1->setGridLineColor(QColor(Qt::darkBlue));
    axisY1->setGridLineVisible(false);                    //设置Y轴网格不显示
    axisY1->setLinePen(penY);
    axisX->setLinePen(penY);

    splinechart->addAxis(axisX,Qt::AlignBottom);               //设置坐标轴位于chart中的位置
    splinechart->addAxis(axisY,Qt::AlignLeft);//图表的左边
    splinechart->addAxis(axisY1,Qt::AlignRight);//图表的右边

    splinechart->setTheme(QChart::ChartThemeDark);           //设置图标主题

    series->attachAxis(axisX);                           //把数据添加到坐标轴上
    series->attachAxis(axisY);
    series->setName("相对湿度变化");
    series1->attachAxis(axisX);                           //把数据添加到坐标轴上
    series1->attachAxis(axisY1);
    series1->setName("绝对湿度变化");

    axisY->setTitleText("相对湿度/RH");
    axisY1->setTitleText("绝对湿度/g/m^3");


    //把chart显示到窗口上
    chartView->setChart(splinechart);
    //ui->widget->setChart(chart);
    //ui->widget->setRenderHint(QPainter::Antialiasing);   //设置抗锯齿
}
double rand_back1(double i,double j) { //生成正太分布的随机数据
    double u1=double(rand()%1000)/1000,u2=double(rand()%1000)/1000,r;
    //static unsigned int seed=0;
    r=i+sqrt(j)*sqrt(-2.0*(log(u1)/log(exp(1.0))))*cos(2*pi*u2);
    return r;
}
double humimage::productreduce(designscene *a){
    int eachwindowreduce=150;
    double reduce=a->ifwindow*eachwindowreduce;//窗体对制冷量的损耗
    return reduce;
}
double humimage::productsimulate(airnum a,designscene *b,double in,double out){
    int windV=a.airvolume;//循环风量
    double daore=b->roomk.heats;//导热系数
    double s=b->rooms;//墙的面积
    double wallwidth=b->roomwidth;//墙的厚度
    double Qchange=daore*s*(out-in)/wallwidth;//外界热传导进入房间的温度（傅里叶热传导公式）


    double icew=(a.icecapacity-productreduce(b)-Qchange)*0.8598;//制冷量 单位转换 减去消耗量
    double temchange=icew/(k*Cp*windV*60);//每过1分钟变化的温度
    return temchange;

}
void humimage::producttemvector(){

    int shu=10;
    srand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i=0;i<25;i++){
        temvector.push_back(shu);
    }
    int sunrise=6;
    int sundown=18;

    for (int i = 0; i < sunrise; i++) {
        temvector[i]=rand_back(temcount-3, 1);
    }
    QVector<double> a;
    srand( (unsigned)time( NULL ) );
    for (int i = sunrise; i <= 14; i++) {
        a.push_back(rand_back(temcount,3.0));
        std::sort(a.begin(),a.end());

    }


    //QList<double>::iterator it;  //构建一个list容器的迭代器it
    for(int i=0;i<a.size();i++){
        temvector[i+sunrise]=a[i];
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
void humimage::getpoint()
{
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
    static double refreshtem1;static double number1;
    int refreshtime=10;
    starttime=QTime(b.sh,b.smin,0,0);
    endtime=QTime(b.eh,b.emin,0,0);

    if(work51==0){//只初始化一次
        humtime=new QDateTime(QDateTime::currentDateTime().date(),QTime(starttime.hour(),starttime.minute(),0,0));//为画线的时间初始化
        airtime1=new QDateTime(QDateTime::currentDateTime().date(),QTime(starttime.hour(),starttime.minute(),0,0));
        number1 =temvector[starttime.hour()];
        relhum=humvector[starttime.hour()];
        abshum=whichabshum(relhum,whichtem(number1));//初始绝对湿度和相对湿度
        refreshtem1=b.tem;//应该是运行的最后一次温度无法获取
        work51=1;
    }    //QTime mintime=airtime.addSecs(0);
    //QTime maxtime=airtime.addSecs(60);
    //QDateTime currentTime = QDateTime::currentDateTime();
    //设置坐标轴显示范围***************************************************************
    //splinechart->axisX()->setMin(QDateTime::currentDateTime().addSecs(-60 * 1));       //系统当前时间的前一秒
    //splinechart->axisX()->setMax(QDateTime::currentDateTime().addSecs(0));            //系统当前时间
    //splinechart->axisX()->setMax();
    double change=productsimulate(a->airk,a,number1,temvector[airtime1->time().hour()]);//生成改变量
    //qDebug()<<change;

    splinechart->axisX()->setMin(airtime1->addSecs(-60*15));//画图，这个应该与有多少个间隔来决定
    splinechart->axisX()->setMax(airtime1->addSecs(0));
    if((a->ifair!=0&&a->openair!=0)||(a->ifairtwo!=0&&a->openairtwo!=0)){
    if(endtime<airtime1->time()){//回温设置
        if(refreshtem1>temvector[endtime.hour()]){
            *airtime1=airtime1->addSecs(0);
            work100=1;
        }
        else{
            *airtime1=airtime1->addSecs(60);
            double eachlengthtem=(temvector[endtime.hour()]-b.tem)/refreshtime;//使用空调结束运行时的外界温度


            refreshtem1+=eachlengthtem;
            simatetem=refreshtem1;
            //series->append(airtime1->toMSecsSinceEpoch(),refreshtem1);
            //series1->append(airtime1->toMSecsSinceEpoch(),b.tem);


        }


    }
    else{
        *airtime1=airtime1->addSecs(60 * 1);//每隔30分钟画一个点                        //这里生成随机数做测试
        std::default_random_engine e(time(0));
        std::uniform_real_distribution<double> u1(-0.12, 0.12);
        //增加新的点到曲线末端
        //series->append(airtime1->toMSecsSinceEpoch(),number1);
        //series1->append(airtime1->toMSecsSinceEpoch(),b.tem);
        simatetem=number1;



        if(number1<b.tem){//变频设置
            work61=1;
            number1+=u1(e);
        }
        else{
            if(work61==0){
                number1-=(change+u1(e));
            }
            else{
                number1-=u1(e);
            }
        }


    }
    }
    else{
        //不开空调时为外界温度
        *airtime1=airtime1->addSecs(60);
        simatetem=temvector[airtime1->time().hour()];
    }
qDebug()<<"wendu"<<simatetem;
}
humimage::~humimage()
{
    delete ui;
}
void humimage::loadhum(){
QVector<double> hum5;
hum5.push_back(0.34);
hum5.push_back(0.68);
hum5.push_back(1.02);
hum5.push_back(1.36);
hum5.push_back(1.70);
hum5.push_back(2.04);
hum5.push_back(2.38);
hum5.push_back(2.72);
hum5.push_back(3.06);
hum5.push_back(3.40);
hum5.push_back(3.73);
hum5.push_back(4.07);
hum5.push_back(4.41);
hum5.push_back(4.75);
hum5.push_back(5.09);
hum5.push_back(5.43);
hum5.push_back(5.77);
hum5.push_back(6.11);
hum5.push_back(6.45);
hum5.push_back(6.79);
hum.push_back(hum5);

QVector<double> hum10;
hum10.push_back(0.47);
hum10.push_back(0.94);
hum10.push_back(1.41);
hum10.push_back(1.88);
hum10.push_back(2.35);
hum10.push_back(2.82);
hum10.push_back(3.29);
hum10.push_back(3.76);
hum10.push_back(4.23);
hum10.push_back(4.70);
hum10.push_back(5.16);
hum10.push_back(5.63);
hum10.push_back(6.10);
hum10.push_back(6.57);
hum10.push_back(7.04);
hum10.push_back(7.51);
hum10.push_back(7.98);
hum10.push_back(8.45);
hum10.push_back(8.92);
hum10.push_back(9.39);
hum.push_back(hum10);

QVector<double> hum15;
hum15.push_back(0.64);
hum15.push_back(1.28);
hum15.push_back(1.92);
hum15.push_back(2.56);
hum15.push_back(3.21);
hum15.push_back(3.85);
hum15.push_back(4.49);
hum15.push_back(5.13);
hum15.push_back(5.77);
hum15.push_back(6.41);
hum15.push_back(7.05);
hum15.push_back(7.89);
hum15.push_back(8.33);
hum15.push_back(8.97);
hum15.push_back(9.02);
hum15.push_back(10.28);
hum15.push_back(10.90);
hum15.push_back(11.54);
hum15.push_back(12.10);
hum15.push_back(12.82);
hum.push_back(hum15);

QVector<double> hum20;
hum20.push_back(0.86);
hum20.push_back(1.73);
hum20.push_back(2.59);
hum20.push_back(3.45);
hum20.push_back(4.32);
hum20.push_back(5.18);
hum20.push_back(6.04);
hum20.push_back(6.91);
hum20.push_back(7.77);
hum20.push_back(8.64);
hum20.push_back(9.50);
hum20.push_back(10.36);
hum20.push_back(11.23);
hum20.push_back(12.09);
hum20.push_back(12.95);
hum20.push_back(13.82);
hum20.push_back(14.68);
hum20.push_back(15.54);
hum20.push_back(16.41);
hum20.push_back(17.27);
hum.push_back(hum20);

QVector<double> hum25;
hum25.push_back(1.15);
hum25.push_back(2.3);
hum25.push_back(3.45);
hum25.push_back(4);
hum25.push_back(5.75);
hum25.push_back(6.90);
hum25.push_back(8.05);
hum25.push_back(9.20);
hum25.push_back(10.35);
hum25.push_back(11.51);
hum25.push_back(12.66);
hum25.push_back(13.81);
hum25.push_back(14.96);
hum25.push_back(16.11);
hum25.push_back(17.26);
hum25.push_back(18.41);
hum25.push_back(19.56);
hum25.push_back(20.71);
hum25.push_back(21.86);
hum25.push_back(23.01);
hum.push_back(hum25);

QVector<double> hum30;
hum30.push_back(1.52);
hum30.push_back(3.03);
hum30.push_back(4.55);
hum30.push_back(6.06);
hum30.push_back(7.58);
hum30.push_back(9.09);
hum30.push_back(10.61);
hum30.push_back(12.12);
hum30.push_back(13.64);
hum30.push_back(15.16);
hum30.push_back(16.67);
hum30.push_back(18.19);
hum30.push_back(19.70);
hum30.push_back(21.22);
hum30.push_back(22.73);
hum30.push_back(24.25);
hum30.push_back(25.76);
hum30.push_back(27.28);
hum30.push_back(28.79);
hum30.push_back(30.31);
hum.push_back(hum30);

QVector<double> hum35;
hum35.push_back(1.98);
hum35.push_back(3.95);
hum35.push_back(5.93);
hum35.push_back(7.90);
hum35.push_back(9.88);
hum35.push_back(11.85);
hum35.push_back(13.83);
hum35.push_back(15.80);
hum35.push_back(17.78);
hum35.push_back(19.76);
hum35.push_back(21.73);
hum35.push_back(23.71);
hum35.push_back(25.68);
hum35.push_back(27.66);
hum35.push_back(29.63);
hum35.push_back(31.61);
hum35.push_back(33.58);
hum35.push_back(35.56);
hum35.push_back(37.53);
hum35.push_back(39.51);
hum.push_back(hum35);

QVector<double> hum40;
hum40.push_back(2.55);
hum40.push_back(5.10);
hum40.push_back(7.65);
hum40.push_back(10.20);
hum40.push_back(12.75);
hum40.push_back(15.30);
hum40.push_back(17.85);
hum40.push_back(20.40);
hum40.push_back(22.95);
hum40.push_back(25.50);
hum40.push_back(28.05);
hum40.push_back(30.60);
hum40.push_back(33.15);
hum40.push_back(35.70);
hum40.push_back(38.25);
hum40.push_back(40.80);
hum40.push_back(43.35);
hum40.push_back(45.90);
hum40.push_back(48.45);
hum40.push_back(51);
hum.push_back(hum40);
}
void humimage::setunit(){

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
void humimage::gettime(){
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











    //获取上下线










}
void humimage::withdesign(){
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

    //除湿器的开关
    if(designk->ifdehum==0){
        ui->label_43->hide();
        open10->hide();
    }
    if(designk->ifhum==0){
        ui->label_42->hide();
        open9->hide();
    }
    if(designb->ifdehum==0){
        ui->label_41->hide();
        open12->hide();
    }
    if(designb->ifhum==0){
        ui->label_40->hide();
        open11->hide();
    }
    if(designw->ifdehum==0){
        ui->label_45->hide();
        open14->hide();
    }
    if(designw->ifhum==0){
        ui->label_44->hide();
        open13->hide();
    }
    if(designl->ifdehum==0){
        ui->label_47->hide();
        open16->hide();
    }
    if(designl->ifhum==0){
        ui->label_46->hide();
        open15->hide();
    }

}
void humimage::setbutton(){
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
        designk->openair=1;

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
        designk->openair=0;
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
        designk->openairtwo=1;
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

      designk->openairtwo=0;

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

    open9=new mypushbutton(":/mainscene/mnjj/mainscene/open.png");//,":/mainscene/mnjj/mainscene/close.png"
    open9->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    open9->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    open9->setParent(ui->tab);//ui->widget在design上面
    open9->move(200,600);//按钮的高度与ok1-》height不同
    open9->setFixedSize(80,60);
    open9->setIconSize(QSize(80,60));

    close9=new mypushbutton(":/mainscene/mnjj/mainscene/close.png");//,":/mainscene/mnjj/mainscene/close.png"
    close9->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    close9->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    close9->setParent(ui->tab);//ui->widget在design上面
    close9->move(200,600);//按钮的高度与ok1-》height不同
    close9->setFixedSize(80,60);
    close9->setIconSize(QSize(80,60));
    close9->hide();
    connect(close9, &mypushbutton::clicked, [=]() {
        close9->zoom1();
        close9->zoom2();
        openhum1=1;
        designk->openhum=true;
        QTimer::singleShot(500,this,[=](){
            close9->hide();
            open9->show();
        });
    });
    connect(open9, &mypushbutton::clicked, [=]() {
        open9->zoom1();
        open9->zoom2();
        openhum1=0;
        designk->openhum=0;
        QTimer::singleShot(500,this,[=](){
            open9->hide();
            close9->show();
        });
    });



    open10=new mypushbutton(":/mainscene/mnjj/mainscene/open.png");//,":/mainscene/mnjj/mainscene/close.png"
    open10->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    open10->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    open10->setParent(ui->tab);//ui->widget在design上面
    open10->move(200,700);//按钮的高度与ok1-》height不同
    open10->setFixedSize(80,60);
    open10->setIconSize(QSize(80,60));

    close10=new mypushbutton(":/mainscene/mnjj/mainscene/close.png");//,":/mainscene/mnjj/mainscene/close.png"
    close10->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    close10->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    close10->setParent(ui->tab);//ui->widget在design上面
    close10->move(200,700);//按钮的高度与ok1-》height不同
    close10->setFixedSize(80,60);
    close10->setIconSize(QSize(80,60));
    close10->hide();
    connect(close10, &mypushbutton::clicked, [=]() {
        close10->zoom1();
        close10->zoom2();
        opendehum1=1;
        designk->opendehum=true;
        QTimer::singleShot(500,this,[=](){
            close10->hide();
            open10->show();
        });
    });
    connect(open10, &mypushbutton::clicked, [=]() {
        open10->zoom1();
        open10->zoom2();
        opendehum1=0;
        designk->opendehum=0;
        QTimer::singleShot(500,this,[=](){
            open10->hide();
            close10->show();
        });
    });

    open11=new mypushbutton(":/mainscene/mnjj/mainscene/open.png");//,":/mainscene/mnjj/mainscene/close.png"
    open11->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    open11->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    open11->setParent(ui->tab_2);//ui->widget在design上面
    open11->move(200,600);//按钮的高度与ok1-》height不同
    open11->setFixedSize(80,60);
    open11->setIconSize(QSize(80,60));

    close11=new mypushbutton(":/mainscene/mnjj/mainscene/close.png");//,":/mainscene/mnjj/mainscene/close.png"
    close11->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    close11->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    close11->setParent(ui->tab_2);//ui->widget在design上面
    close11->move(200,600);//按钮的高度与ok1-》height不同
    close11->setFixedSize(80,60);
    close11->setIconSize(QSize(80,60));
    close11->hide();
    connect(close11, &mypushbutton::clicked, [=]() {
        close11->zoom1();
        close11->zoom2();
        openhum2=1;
        designb->openhum=1;
        QTimer::singleShot(500,this,[=](){
            close11->hide();
            open11->show();
        });
    });
    connect(open11, &mypushbutton::clicked, [=]() {
        open11->zoom1();
        open11->zoom2();
        openhum2=0;
        designb->openhum=0;
        QTimer::singleShot(500,this,[=](){
            open11->hide();
            close11->show();
        });
    });

    open12=new mypushbutton(":/mainscene/mnjj/mainscene/open.png");//,":/mainscene/mnjj/mainscene/close.png"
    open12->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    open12->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    open12->setParent(ui->tab_2);//ui->widget在design上面
    open12->move(200,700);//按钮的高度与ok1-》height不同
    open12->setFixedSize(80,60);
    open12->setIconSize(QSize(80,60));

    close12=new mypushbutton(":/mainscene/mnjj/mainscene/close.png");//,":/mainscene/mnjj/mainscene/close.png"
    close12->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    close12->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    close12->setParent(ui->tab_2);//ui->widget在design上面
    close12->move(200,700);//按钮的高度与ok1-》height不同
    close12->setFixedSize(80,60);
    close12->setIconSize(QSize(80,60));
    close12->hide();
    connect(close12, &mypushbutton::clicked, [=]() {
        close12->zoom1();
        close12->zoom2();
        opendehum2=1;
        designb->opendehum=1;
        QTimer::singleShot(500,this,[=](){
            close12->hide();
            open12->show();
        });
    });
    connect(open12, &mypushbutton::clicked, [=]() {
        open12->zoom1();
        open12->zoom2();
        opendehum2=0;
        designb->opendehum=0;
        QTimer::singleShot(500,this,[=](){
            open12->hide();
            close12->show();
        });
    });

    open13=new mypushbutton(":/mainscene/mnjj/mainscene/open.png");//,":/mainscene/mnjj/mainscene/close.png"
    open13->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    open13->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    open13->setParent(ui->tab_3);//ui->widget在design上面
    open13->move(200,600);//按钮的高度与ok1-》height不同
    open13->setFixedSize(80,60);
    open13->setIconSize(QSize(80,60));

    close13=new mypushbutton(":/mainscene/mnjj/mainscene/close.png");//,":/mainscene/mnjj/mainscene/close.png"
    close13->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    close13->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    close13->setParent(ui->tab_3);//ui->widget在design上面
    close13->move(200,600);//按钮的高度与ok1-》height不同
    close13->setFixedSize(80,60);
    close13->setIconSize(QSize(80,60));
    close13->hide();
    connect(close13, &mypushbutton::clicked, [=]() {
        close13->zoom1();
        close13->zoom2();
        openhum3=1;
        designw->openhum=1;

        QTimer::singleShot(500,this,[=](){
            close13->hide();
            open13->show();
        });
    });
    connect(open13, &mypushbutton::clicked, [=]() {
        open13->zoom1();
        open13->zoom2();
        openhum3=0;
      designw->openhum=0;
        QTimer::singleShot(500,this,[=](){
            open13->hide();
            close13->show();
        });
    });

    open14=new mypushbutton(":/mainscene/mnjj/mainscene/open.png");//,":/mainscene/mnjj/mainscene/close.png"
    open14->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    open14->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    open14->setParent(ui->tab_3);//ui->widget在design上面
    open14->move(200,700);//按钮的高度与ok1-》height不同
    open14->setFixedSize(80,60);
    open14->setIconSize(QSize(80,60));

    close14=new mypushbutton(":/mainscene/mnjj/mainscene/close.png");//,":/mainscene/mnjj/mainscene/close.png"
    close14->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    close14->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    close14->setParent(ui->tab_3);//ui->widget在design上面
    close14->move(200,700);//按钮的高度与ok1-》height不同
    close14->setFixedSize(80,60);
    close14->setIconSize(QSize(80,60));
    close14->hide();
    connect(close14, &mypushbutton::clicked, [=]() {
        close14->zoom1();
        close14->zoom2();
        opendehum3=1;
                designw->opendehum=1;
        QTimer::singleShot(500,this,[=](){
            close14->hide();
            open14->show();
        });
    });
    connect(open14, &mypushbutton::clicked, [=]() {
        open14->zoom1();
        open14->zoom2();
        opendehum3=0;
                designw->opendehum=0;
        QTimer::singleShot(500,this,[=](){
            open14->hide();
            close14->show();
        });
    });

    open15=new mypushbutton(":/mainscene/mnjj/mainscene/open.png");//,":/mainscene/mnjj/mainscene/close.png"
    open15->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    open15->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    open15->setParent(ui->tab_4);//ui->widget在design上面
    open15->move(200,600);//按钮的高度与ok1-》height不同
    open15->setFixedSize(80,60);
    open15->setIconSize(QSize(80,60));

    close15=new mypushbutton(":/mainscene/mnjj/mainscene/close.png");//,":/mainscene/mnjj/mainscene/close.png"
    close15->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    close15->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    close15->setParent(ui->tab_4);//ui->widget在design上面
    close15->move(200,600);//按钮的高度与ok1-》height不同
    close15->setFixedSize(80,60);
    close15->setIconSize(QSize(80,60));
    close15->hide();
    connect(close15, &mypushbutton::clicked, [=]() {
        close15->zoom1();
        close15->zoom2();
        openhum4=1;
                designl->openhum=1;
        QTimer::singleShot(500,this,[=](){
            close15->hide();
            open15->show();
        });
    });
    connect(open15, &mypushbutton::clicked, [=]() {
        open15->zoom1();
        open15->zoom2();
        openhum4=0;
                designl->openhum=0;
        QTimer::singleShot(500,this,[=](){
            open15->hide();
            close15->show();
        });
    });

    open16=new mypushbutton(":/mainscene/mnjj/mainscene/open.png");//,":/mainscene/mnjj/mainscene/close.png"
    open16->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    open16->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    open16->setParent(ui->tab_4);//ui->widget在design上面
    open16->move(200,700);//按钮的高度与ok1-》height不同
    open16->setFixedSize(80,60);
    open16->setIconSize(QSize(80,60));

    close16=new mypushbutton(":/mainscene/mnjj/mainscene/close.png");//,":/mainscene/mnjj/mainscene/close.png"
    close16->setStyleSheet("background-color:#aaaaaa;");//设计的按钮通过更换成所在控件的背景色，实现不留白
    close16->setStyleSheet("QPushButton:hover{border-image: url(:/design/mnjj/design/no1.png);background-color:#aaaaaa;}");
    close16->setParent(ui->tab_4);//ui->widget在design上面
    close16->move(200,700);//按钮的高度与ok1-》height不同
    close16->setFixedSize(80,60);
    close16->setIconSize(QSize(80,60));
    close16->hide();
    connect(close16, &mypushbutton::clicked, [=]() {
        close16->zoom1();
        close16->zoom2();
        opendehum4=1;
                designl->opendehum=1;
        QTimer::singleShot(500,this,[=](){
            close16->hide();
            open16->show();
        });
    });
    connect(open16, &mypushbutton::clicked, [=]() {
        open16->zoom1();
        open16->zoom2();
        opendehum4=0;
        designl->opendehum=0;
        QTimer::singleShot(500,this,[=](){
            open16->hide();
            close16->show();
        });
    });

}



