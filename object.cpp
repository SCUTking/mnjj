#include "object.h"

object::object(QWidget *parent)
    : QWidget{parent}
{
    this->move(1400,0);
    this->resize(600,1200);
    setStyleSheet("background-color:#ffffff;"
                       "border-radius:5px;"//设置圆角边框
                        //"border:3px solid #abc;"//优化边框（边框有纹路）#include"mypushbutton.h" #include"QTimer"
                       );
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    hide();

}
