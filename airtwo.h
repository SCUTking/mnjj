#ifndef AIRTWO_H
#define AIRTWO_H

#include <QWidget>
#include"mypushbutton.h"
#include"QList"
//#include"QVector"
namespace Ui {
class airtwo;
}

class airtwo : public QWidget
{
    Q_OBJECT

public:
    explicit airtwo(QWidget *parent = nullptr,int* a=0);
    ~airtwo();
    mypushbutton* cut=NULL;
    mypushbutton* ok1=NULL;
void combox();
private:
    Ui::airtwo *ui;
};
struct airtwonum{
    int icecapacity;
    int icew;
    int heatcapacity;
    int heatw;
    int airvolume;
    int horse;
    int source;
};
extern QVector<airtwonum> airtwonums;
#endif // AIRTWO_H
