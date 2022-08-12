#ifndef ALLMAIN_H
#define ALLMAIN_H

#include <QMainWindow>
#include"mainscene.h"
#include"choose_city.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Allmain; }
QT_END_NAMESPACE

class Allmain : public QMainWindow
{
    Q_OBJECT

public:
    Allmain(QWidget *parent = nullptr);
    ~Allmain();
    //画背景
    void paintEvent(QPaintEvent*);

    //主场景

    choose_city* citychoose=NULL;
private:
    Ui::Allmain *ui;
};
#endif // ALLMAIN_H
