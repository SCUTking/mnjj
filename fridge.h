#ifndef FRIDGE_H
#define FRIDGE_H

#include <QWidget>
#include"mypushbutton.h"
#include"QList"
#include"QVector"
namespace Ui {
class frigde;
}

class frigde : public QWidget
{
    Q_OBJECT

public:
    explicit frigde(QWidget *parent = nullptr);
    ~frigde();
    mypushbutton* cut=NULL;
    mypushbutton* ok1=NULL;
    void combox();

private:
    Ui::frigde *ui;
};
struct fridgenum{
    int ice;
    int v;
    int source;
};
extern QVector<fridgenum> fridgenums;
#endif // FRIDGE_H
