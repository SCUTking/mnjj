#ifndef DEHUMIDIFIER_H
#define DEHUMIDIFIER_H

#include <QWidget>
#include"mypushbutton.h"
#include"QTimer"
#include"QVector"
namespace Ui {
class dehumidifier;
}

class dehumidifier : public QWidget
{
    Q_OBJECT

public:
    explicit dehumidifier(QWidget *parent = nullptr,int* a=0,double* checkmax=0);

    ~dehumidifier();
    mypushbutton* cut=NULL;
    mypushbutton* ok1=NULL;
    void combox();
private:
    Ui::dehumidifier *ui;
};
struct dehumnum{
    int w;
    double waterv;
    int size;
    int dehumc;
};
extern QVector<dehumnum> dehumnums;
#endif // DEHUMIDIFIER_H
