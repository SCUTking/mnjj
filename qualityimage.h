#ifndef QUALITYIMAGE_H
#define QUALITYIMAGE_H

#include <QWidget>
//Qtcharts四个头文件
#include <QWidget>
#include"QLabel"
#include <QtCharts>
#include"QTimer"

#include <QChartView>
#include"humimage.h"
#include <QSplineSeries>
#include"designscene.h"
#include"temimage.h"
#include"mypushbutton.h"
namespace Ui {
class qualityimage;
}

class qualityimage : public humimage
{
    Q_OBJECT

public:


    int whichdesign1=0;
    explicit qualityimage(QWidget *parent = nullptr,designscene* designk=NULL,designscene* designl=NULL,designscene* designw=NULL,designscene* designb=NULL);
    //~qualityimage();
    //mypushbutton* no;
    virtual void startchart();
    QChart *qulsplinechart;                           //画布

    QSplineSeries *series2;  //空气曲线
    QChartView *qulchartView;
    void initchart();
    QDateTimeAxis *axisx2;                    //轴
    QValueAxis *axisy2;
    double qul=0;
    double getqul(int setqul);
    void addqulview();
    QVector<double> qulvector;
    QLabel* qulview;
    QDateTime* humtime1;//湿度



private:
    //Ui::qualityimage *ui;
    //QChart *mChart;
public slots:
    void quldrawline();
    void drawpoint();

};

#endif // QUALITYIMAGE_H
