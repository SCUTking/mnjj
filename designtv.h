#ifndef DESIGNTV_H
#define DESIGNTV_H

#include <QWidget>
#include"mypushbutton.h"
namespace Ui {
class designtv;
}

class designtv : public QWidget
{
    Q_OBJECT

public:
    explicit designtv(QWidget *parent = nullptr);
    ~designtv();
    mypushbutton* cut=NULL;
    mypushbutton* ok1=NULL;//确认控件设为成员，以便其他类进行访问

private:
    Ui::designtv *ui;
};

#endif // DESIGNTV_H
