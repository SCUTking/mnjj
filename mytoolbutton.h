#ifndef MYTOOLBUTTON_H
#define MYTOOLBUTTON_H

#include <QWidget>
#include"QToolButton"
class mytoolbutton : public QToolButton
{
    Q_OBJECT
public:
    //explicit mypushbutton(QWidget *parent = nullptr);
    mytoolbutton(QString normalImg, QString pressImg = "");
       //成员函数
       QString normalImgPath;
       QString pressImgPath;
       void zoom1();
       void zoom2();
       //重写鼠标按下
       void mousePressEvent(QMouseEvent* e);
       void mouseReleaseEvent(QMouseEvent* e);
signals:

};

#endif // MYTOOLBUTTON_H
