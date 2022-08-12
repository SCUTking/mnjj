#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include"designscene.h"
#include"qualityimage.h"
#include"temimage.h"
#include"humimage.h"
#include"mypushbutton.h"
#include"designnewwind.h"
#include"designdinuan.h"

namespace Ui {
class mainscene;
}

class mainscene : public QWidget
{
    Q_OBJECT

public:
    explicit mainscene(QWidget *parent = nullptr);
    ~mainscene();
    //定义4个窗口
    designscene* designk=NULL;
    designscene* designl=NULL;
    designscene* designw=NULL;
    designscene* designb=NULL;





    qualityimage* quaimg=NULL;
    designnewwind* nwind=NULL;
    designdinuan* dnuan=NULL;
    temimage* temimg=NULL;
    humimage* humimg=NULL;
    mypushbutton* no;

    void loadimg();
    void loadbutton();
private:
    Ui::mainscene *ui;

};

#endif // MAINSCENE_H
