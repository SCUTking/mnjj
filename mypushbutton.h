#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include<QPushButton>

class mypushbutton : public QPushButton
{
    Q_OBJECT
public:
    //explicit mypushbutton(QWidget *parent = nullptr);
    mypushbutton(QString normalImg, QString pressImg = "");
       //成员函数
       QString normalImgPath;
       QString pressImgPath;
       void zoom1();
       void zoom2();
       //重写鼠标按下
       void mousePressEvent(QMouseEvent* e);
       void mouseReleaseEvent(QMouseEvent* e);
        void mouseMoveEvent(QMouseEvent *e);

       bool isactive;
signals:

};

#endif // MYPUSHBUTTON_H
