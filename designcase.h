#ifndef DESIGNCASE_H
#define DESIGNCASE_H

#include <QWidget>
#include"mypushbutton.h"
namespace Ui {
class designcase;
}

class designcase : public QWidget
{
    Q_OBJECT

public:
    explicit designcase(QWidget *parent = nullptr);
    ~designcase();
    mypushbutton* cut=NULL;
    mypushbutton* ok1=NULL;//确认控件设为成员，以便其他类进行访问

private:
    Ui::designcase *ui;
};

#endif // DESIGNCASE_H
