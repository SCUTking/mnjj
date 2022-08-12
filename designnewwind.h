#ifndef DESIGNNEWWIND_H
#define DESIGNNEWWIND_H

#include <QWidget>
#include"mypushbutton.h"

namespace Ui {
class designnewwind;
}

class designnewwind : public QWidget
{
    Q_OBJECT

public:
    explicit designnewwind(QWidget *parent = nullptr);
    ~designnewwind();
    mypushbutton* no;
    mypushbutton* ok1;
    static bool ifchangetem;
    void ifnewwind();
    static bool isnewwind;
    static bool isopennewwind;


private:
    Ui::designnewwind *ui;
};

#endif // DESIGNNEWWIND_H
