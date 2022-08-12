#ifndef DESIGNAIR_H
#define DESIGNAIR_H

#include <QWidget>
#include"mypushbutton.h"

#include"QVector"
namespace Ui {
class designair;
}

class designair : public QWidget
{
    Q_OBJECT

public:
    explicit designair(QWidget *parent = nullptr,int* a=0,double* checkhum=0);
    ~designair();
    Ui::designair *ui;//公告访问
    mypushbutton* cut=NULL;
    mypushbutton* ok1=NULL;//确认控件设为成员，以便其他类进行访问
    void combox();


    double checktem=30;
private:

};
struct airnum{
    int icecapacity;
    int icew;
    int heatcapacity;
    int heatw;
    int airvolume;
    double horse;
    int source;
};

extern QVector<airnum> airnums;
#endif // DESIGNAIR_H
