#ifndef DESIGNSCENE_H
#define DESIGNSCENE_H

#include <QWidget>
#include"QLineEdit"
#include"QLabel"
#include"mypushbutton.h"
#include"QString"
#include"designair.h"
#include"designroom.h"
#include"designbed.h"
#include"designcase.h"
#include"designtv.h"
#include"designdesk.h"
#include"humidifier.h"
#include"dehumidifier.h"
#include"fridge.h"
#include"airtwo.h"
namespace Ui {
class designscene;
}

class designscene : public QWidget
{
    Q_OBJECT

public:
    explicit designscene(QWidget *parent = nullptr);
    ~designscene();
void changepicture1(QLineEdit* lineedit,mypushbutton* putton,QLabel* picture,QString pix);
void changepicture2(QLineEdit* lineedit,mypushbutton* putton,QLabel* picture,QString pix);
void changepicture3(QLineEdit* lineedit,mypushbutton* putton,QLabel* picture,QString pix);

//mypushbutton*airtrue=NULL;
designair* air=NULL;
dehumidifier* ddehumidifier=NULL;
frigde* dfridge=NULL;
humidifier* dhumidifier=NULL;

designroom* room=NULL;
designbed* dbed=NULL;
designcase* dcase=NULL;
designtv* dtv=NULL;

mypushbutton* back;

designdesk* ddesk=NULL;

airtwo* dairtwo=NULL;
designbed* dknife=NULL;
designbed* dbowl=NULL;
designbed* dbowl1=NULL;
designbed* dclock=NULL;
designbed* dcooker=NULL;
designbed* deatdesk=NULL;
designbed* dlight=NULL;
designbed* dpan=NULL;
designbed* dplant=NULL;
designbed* dsalt=NULL;
designbed* dsark1=NULL;
designbed* dsark2=NULL;
designbed* dsark3=NULL;
designbed* dsark4=NULL;
designbed* dshower=NULL;
designbed* dsofa=NULL;
designbed* dstool=NULL;
designbed* dtea=NULL;
designbed* dwashbasin=NULL;
designbed* dwashcloth=NULL;
designbed* dwiredesk=NULL;



mypushbutton* airtrue;
int work=1;
mypushbutton* desktrue;
int work1=1;//只进行一次
mypushbutton* tvtrue;
int work2=1;//只进行一次
mypushbutton* bedtrue;
int work3=1;//只进行一次
mypushbutton* fcasetrue;
int work4=1;//只进行一次
mypushbutton* knifetrue;
int work5=1;//只进行一次
mypushbutton* bowltrue;
int work6=1;//只进行一次
mypushbutton* bowl1true;
int work7=1;//只进行一次
mypushbutton* clocktrue;//true为在房间的，d为设计，无为列表
int work8=1;//只进行一次
mypushbutton* cookertrue;//true为在房间的，d为设计，无为列表
int work9=1;//只进行一次
mypushbutton* eatdesktrue;//true为在房间的，d为设计，无为列表
int work10=1;//只进行一次
mypushbutton* lighttrue;//true为在房间的，d为设计，无为列表
int work11=1;//只进行一次
mypushbutton* pantrue;//true为在房间的，d为设计，无为列表
int work12=1;//只进行一次
mypushbutton* planttrue;//true为在房间的，d为设计，无为列表
int work13=1;//只进行一次
mypushbutton* salttrue;//true为在房间的，d为设计，无为列表
int work14=1;//只进行一次
mypushbutton* sark1true;//true为在房间的，d为设计，无为列表
int work15=1;//只进行一次
mypushbutton* sark2true;//true为在房间的，d为设计，无为列表
int work16=1;//只进行一次
mypushbutton* sark3true;//true为在房间的，d为设计，无为列表
int work17=1;//只进行一次
mypushbutton* sark4true;//true为在房间的，d为设计，无为列表
int work18=1;//只进行一次
mypushbutton* showertrue;//true为在房间的，d为设计，无为列表
int work19=1;//只进行一次
mypushbutton* sofatrue;//true为在房间的，d为设计，无为列表
int work20=1;//只进行一次
mypushbutton* stooltrue;//true为在房间的，d为设计，无为列表
int work21=1;//只进行一次
mypushbutton* teatrue;//true为在房间的，d为设计，无为列表
int work22=1;//只进行一次
mypushbutton* washbasintrue;//true为在房间的，d为设计，无为列表
int work23=1;//只进行一次
mypushbutton* washclothtrue;//true为在房间的，d为设计，无为列表
int work24=1;//只进行一次
mypushbutton* wiredesktrue;//true为在房间的，d为设计，无为列表
int work25=1;//只进行一次
mypushbutton* fridgetrue;//只初始化一次
int work30=1;//只进行一次

mypushbutton* airtwotrue;//只初始化一次
int work40=1;//只进行一次
mypushbutton* dehumidifiertrue;//只初始化一次
int work32=1;//只进行一
mypushbutton* humidifiertrue;//只初始化一次
int work31=1;//只进行一次



//img的数据
//没在设计界面按确定自动选0
int airwhich=0;
int airtwowhich=0;
int dehumwhich=0;
int humwhich=0;
int roomwhich=0;
int roomwidth=120;
bool ifair=0;
bool ifairtwo=0;
bool ifhum=0;
bool ifdehum=0;
int ifwindow=0;
bool ifTV=0;
bool ifplant=0;

double checkmin=45;
double checkmax=55;
double checktem=30;

//默认的房间大小为：长5，宽4，高3
double roomv=60;
double rooms=94;
airnum airk;
airtwonum airtwok;
roomnum roomk;
humnum humk;
dehumnum dehumk;
int roomwidthk;
bool openair=true;
bool openairtwo=true;
bool openhum=true;
bool opendehum=true;



void copy(QWidget* parent,mypushbutton* a,QString tool,QWidget* design);
void loadres();
private:
    Ui::designscene *ui;
};

#endif // DESIGNSCENE_H
