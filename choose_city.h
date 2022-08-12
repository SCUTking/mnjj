#ifndef CHOOSE_CITY_H
#define CHOOSE_CITY_H

#include <QWidget>
#include"season.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>//网络操作的头文件
#include <QNetworkReply>


#include <QTimer>
#include <QGraphicsBlurEffect>

#include"mypushbutton.h"
#include"mainscene.h"
namespace Ui {
class choose_city;
}

class choose_city : public QWidget
{
    Q_OBJECT

public:
    explicit choose_city(QWidget *parent = nullptr);
    ~choose_city();

    mypushbutton* ok1;
    mypushbutton* no;
//季节选择
    season* chooseseason=NULL;


    static int tem;
    static int hum;
    static int pm25;


private slots:

    void update_time();

    void read_cjson(QNetworkReply *repay);

    void on_CheckBt_clicked();

    //事件过滤器





private:
    //Ui::WeatherQuery *ui;
    Ui::choose_city *ui;
    QString WeatherType(QString intype);

    QNetworkAccessManager manager;   //管理器对象
    QTimer mtime;                    //时间对象

    QString city;
    QString date;
    QString high;
    QString low;
    QString fengxiang;
    QString fengli;
    QString type;
    QString ganmao;
    QString temperature;

    QMap<QString,QString> Citys;
};

#endif // CHOOSE_CITY_H
