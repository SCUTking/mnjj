#ifndef DESIGNBED_H
#define DESIGNBED_H

#include <QWidget>
#include"mypushbutton.h"
namespace Ui {
class designbed;
}

class designbed : public QWidget
{
    Q_OBJECT

public:
    explicit designbed(QWidget *parent = nullptr);
    ~designbed();
    mypushbutton* cut=NULL;
    mypushbutton* ok1=NULL;//确认控件设为成员，以便其他类进行访问

private:
    Ui::designbed *ui;
};

#endif // DESIGNBED_H
