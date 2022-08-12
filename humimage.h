#ifndef HUMIMAGE_H
#define HUMIMAGE_H




#include <QWidget>
//Qtcharts四个头文件
#include <QWidget>

#include <QtCharts>

#include <QChartView>

#include <QSplineSeries>
#include"designscene.h"
#include"temimage.h"
#include"mypushbutton.h"

extern int work61;
extern int work51;//实现多次模拟
//extern int whichdesign1;
extern int changehum;
extern int work100;//温度停止时湿度也停止


double rand_back1(double i,double j);
namespace Ui {
class humimage;
}

struct startend;
class humimage : public QWidget
{
    Q_OBJECT

public:

    int whichdesign1=0;


    explicit humimage(QWidget *parent = nullptr,designscene* designk=NULL,designscene* designl=NULL,designscene* designw=NULL,designscene* designb=NULL);
    ~humimage();





    designscene* designk=NULL;//将4个design传入temimage
    designscene* designl=NULL;
    designscene* designw=NULL;
    designscene* designb=NULL;

    int humcount=45;//城市湿度    一开始显示到chart上的
    QVector<double> humvector;
    int temcount=23;//城市温度
    QVector<double> temvector;
    int getseasontem(int citytem);
    int getseasonhum(int cityhum);

    QDateTime* airtime1;//空调的起始期间
    QDateTime* humtime;//湿度
    double simatetem;//实时温度，用于模拟湿度


    void setbutton();//载入开关按钮
    void setunit();//设置单位
    void gettime();//获取开始结束时间
    void getair();
    void withdesign();
    void changedata(designscene* a,startend b);

    double sigmoid(double x);
    void BPhum(double tem,double hum);
    QVector <double> p;




    static int whichtem(double a);

    int whichrelhum(double b,int a);
    double whichabshum(int b,int a);

    QVector<QVector<double> > hum;//二维数组
    void loadhum();
    void producttemvector();
    void producthumvector();
    double productsimulate(airnum a,designscene *b,double in,double out);
    double productreduce(designscene* a);
    void initDraw(); //折线图
    virtual void startchart();



    double abshum=12;//画动态图
    double relhum=20;


    startend startend1;
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

//除湿器
    mypushbutton* open9;
    mypushbutton* close9;
    bool openhum1=1;
    mypushbutton* open10;
    mypushbutton* close10;
    bool opendehum1=1;

    mypushbutton* open11;
    mypushbutton* close11;
    bool openhum2=1;
    mypushbutton* open12;
    mypushbutton* close12;
    bool opendehum2=1;

    mypushbutton* open13;
    mypushbutton* close13;
    bool openhum3=1;
    mypushbutton* open14;
    mypushbutton* close14;
    bool opendehum3=1;

    mypushbutton* open15;
    mypushbutton* close15;
    bool openhum4=1;
    mypushbutton* open16;
    mypushbutton* close16;
    bool opendehum4=1;



    Ui::humimage *ui;
    QChartView *chartView;
    QChart *mChart;


    QTimer *timer;
    QChart *splinechart;                           //画布

    QTime starttime;
    QTime endtime;
    QSplineSeries *series;                     //线
    QSplineSeries *series1;//直线
    QDateTimeAxis *axisX;                    //轴
    QValueAxis *axisY;
    QValueAxis *axisY1;


    mypushbutton* no;//不能放到private进去
    mypushbutton* ok1;
private:
    void checkhum(double relhum,designscene* a);
    void checkdehum(double relhum,designscene* a);
    double checkmax=55;
    double checkmin=45;

public slots:

    void getpoint();
    void DrawLine();                            //画线（这里可以考虑使用函数数组）

};

#endif // HUMIMAGE_H
