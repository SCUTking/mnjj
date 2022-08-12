#ifndef SEASON_H
#define SEASON_H

#include <QWidget>
#include"mypushbutton.h"

#include"mainscene.h"
namespace Ui {
class season;
}

class season : public QWidget
{
    Q_OBJECT

public:
    //主场景
    mainscene* mscene=NULL;
    explicit season(QWidget *parent = nullptr);
    ~season();
    void setbutton();
    mypushbutton* no;
static int whichseason;
private:
    Ui::season *ui;
};

#endif // SEASON_H
