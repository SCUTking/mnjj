#ifndef DESIGNDESK_H
#define DESIGNDESK_H

#include <QWidget>
#include"mypushbutton.h"
namespace Ui {
class designdesk;
}

class designdesk : public QWidget
{
    Q_OBJECT

public:
    explicit designdesk(QWidget *parent = nullptr);
    ~designdesk();
    mypushbutton* cut=NULL;
    mypushbutton* ok1=NULL;//确认控件设为成员，以便其他类进行访问
    Ui::designdesk *ui;
private:

};




#endif // DESIGNDESK_H
