#ifndef DESIGNROOM_H
#define DESIGNROOM_H

#include <QWidget>

namespace Ui {
class designroom;
}

class designroom : public QWidget
{
    Q_OBJECT

public:
    explicit designroom(QWidget *parent = nullptr,int* a=0,int* b=0);
    ~designroom();
    Ui::designroom *ui;
private:

};
struct roomnum{
double heatc;
double heats;
};
extern QVector<roomnum> roomnums;
#endif // DESIGNROOM_H
