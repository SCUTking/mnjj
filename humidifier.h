#ifndef HUMIDIFIER_H
#define HUMIDIFIER_H

#include <QWidget>
#include"mypushbutton.h"
#include"QTimer"
#include"QVector"
namespace Ui {
class humidifier;
}

class humidifier : public QWidget
{
    Q_OBJECT

public:
    explicit humidifier(QWidget *parent = nullptr,int* a=0,double* checkmin=0);
    ~humidifier();
    mypushbutton* cut=NULL;
    mypushbutton* ok1=NULL;
void combox();
private:
    Ui::humidifier *ui;
};
struct humnum{
    int sound;
    double waterv;
    int humc;
};
extern QVector<humnum> humnums;
#endif // HUMIDIFIER_H
