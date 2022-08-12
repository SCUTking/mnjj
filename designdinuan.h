#ifndef DESIGNDINUAN_H
#define DESIGNDINUAN_H

#include <QWidget>
#include"mypushbutton.h"

namespace Ui {
class designdinuan;
}

class designdinuan : public QWidget
{
    Q_OBJECT

public:
    explicit designdinuan(QWidget *parent = nullptr);
    ~designdinuan();
    mypushbutton* no;
    mypushbutton* ok1;
        void ifdinuan();
        static bool isdinuan;
        static bool isopendinuan;
        static int temdinuan;

private:
    Ui::designdinuan *ui;
};

#endif // DESIGNDINUAN_H
