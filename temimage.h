#ifndef TEMIMAGE_H
#define TEMIMAGE_H

#include <QWidget>
//Qtcharts四个头文件
#include <QtCharts>

#include <QChartView>

#include <QSplineSeries>
#include"mypushbutton.h"
#include"designscene.h"
#include <QTimer>

#define pi 3.1415926
#define Cp 0.24//(Kcal/(kg*摄氏度))
#define k 1.25//(kg/m^3)空气比重

//QT_CHARTS_USE_NAMESPACE

//QT_CHARTS_USE_NAMESPACE
namespace Ui {
class temimage;
}
struct startend{
    int sh=8;
    int smin=0;
    int eh=10;
    int emin=0;
    int tem=18;
};
double rand_back(double i,double j);
class temimage : public QWidget
{
    Q_OBJECT

public:




    explicit temimage(QWidget *parent =nullptr,designscene* designk=NULL,designscene* designl=NULL,designscene* designw=NULL,designscene* designb=NULL);
    ~temimage();

    designscene* designk=NULL;//将4个design传入temimage
    designscene* designl=NULL;
    designscene* designw=NULL;
    designscene* designb=NULL;

    int temcount=23;//城市温度
    QVector<double> temvector;
    int getseasontem(int citytem);

    void setbutton();//载入开关按钮
    void setunit();//设置单位
    void gettime();//获取开始结束时间
    void getair();
    void withdesign();

    void producttemvector();
    double productnewwind(double intotem,double outtem,designscene* a);
    double productsimulate(airnum a,designscene *b,double in,double out);
    double productreduce(designscene* a);
    void initDraw(); //折线图


    void checktem(double tem,designscene *a);
    double checktemnum=30;



mypushbutton* no;
private:
//厨房
    startend startend1;
    QDateTime* airtime;//空调的起始期间

    mypushbutton* open1;
    mypushbutton* close1;
    bool openair1=1;
    mypushbutton* open2;
    mypushbutton* close2;
    bool openairtwo1=1;
//卧室
    startend startend2;

    mypushbutton* open3;
    mypushbutton* close3;
    bool openair2=1;
    mypushbutton* open4;
    mypushbutton* close4;
    bool openairtwo2=1;



//卫生间
    startend startend3;

    mypushbutton* open5;
    mypushbutton* close5;
    bool openair3=1;
    mypushbutton* open6;
    mypushbutton* close6;
    bool openairtwo3=1;
//客厅
    startend startend4;

    mypushbutton* open7;
    mypushbutton* close7;
    bool openair4=1;
    mypushbutton* open8;
    mypushbutton* close8;
    bool openairtwo4=1;



    QChartView *chartView;
    Ui::temimage *ui;
    QChart *mChart;


    QTimer *timer;
    QChart *splinechart;                           //画布

    QSplineSeries *series;                     //线
    QSplineSeries *series1;//直线
    QDateTimeAxis *axisX;                    //轴
    QValueAxis *axisY;

private slots:

    void DrawLine();                            //画线（这里可以考虑使用函数数组）


};


#endif // TEMIMAGE_H
