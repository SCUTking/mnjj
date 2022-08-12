#include "mytoolbutton.h"


#include"QDebug"
#include"qpropertyanimation.h"

mytoolbutton::mytoolbutton(QString normalImg, QString pressImg) {
    this->pressImgPath = pressImg;
    this->normalImgPath = normalImg;
    QPixmap pix;
    bool ret = pix.load(normalImg);
    if (!ret) {
        //qDebug()<<"加载失败";
        return;
    }
    //设置图片固定大小
    this->setFixedSize(pix.width(), pix.height());
    //设置不规则的图片边框
    this->setStyleSheet("QPushButton{border:Opx;}");//就是这样复制就好
    //设置图标大小
    this->setIconSize(QSize(pix.width(), pix.height()));



    //QPixmap pixmask(":/mnjj/mask.png");
    //pixmask=pixmask.scaled(pix.width(),pix.height());
    //设置图标
    this->setIcon(pix);
    //设置不规则按钮
    //this->setMask();//


    //设置autoraise突起显示
    this->autoRaise();

}
void mytoolbutton::zoom1() {
    //创建动画对象
    QPropertyAnimation* animation1 = new QPropertyAnimation(this, "geometry");//geometry矩形
//设置时间间隔
    animation1->setDuration(200);
    //创建起始位置
    animation1->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    //创建结束位置
    animation1->setEndValue(QRect(this->x(), this->y() - 10, this->width(), this->height()));
    //设置缓和曲线  QEasingCurve::OutBounce弹跳效果
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animation1->start();


}
void mytoolbutton::zoom2() {
    //创建动画对象
    QPropertyAnimation* animation2 = new QPropertyAnimation(this, "geometry");//geometry矩形
//设置时间间隔
    animation2->setDuration(200);
    //创建起始位置
    animation2->setStartValue(QRect(this->x(), this->y() - 10, this->width(), this->height()));
    //创建结束位置
    animation2->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    //设置缓和曲线  QEasingCurve::OutBounce弹跳效果
    animation2->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animation2->start();
}
void mytoolbutton::mousePressEvent(QMouseEvent* e) {
    if (this->pressImgPath != "") {//传入的图片不为空
        QPixmap pix;
        bool ret = pix.load(this->pressImgPath);
        if (!ret) {
            //qDebug()<<"加载失败";
            return;
        }
        //设置图片固定大小
        this->setFixedSize(pix.width(), pix.height());
        //设置不规则的图片边框
        this->setStyleSheet("QPushButton{border:Opx;}");//就是这样复制就好
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(), pix.height()));
    }
    return QToolButton::mousePressEvent(e);

}
void mytoolbutton::mouseReleaseEvent(QMouseEvent* e) {
    if (this->pressImgPath != "") {//传入的图片不为空
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath);
        if (!ret) {
            //qDebug()<<"加载失败";
            return;
        }
        //设置图片固定大小
        this->setFixedSize(pix.width(), pix.height());
        //设置不规则的图片边框
        this->setStyleSheet("QPushButton{border:Opx;}");//就是这样复制就好
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(), pix.height()));
    }
    //让qpushbutton执行其他内容
    return QToolButton::mouseReleaseEvent(e);
}

