#ifndef OBJECT_H
#define OBJECT_H

#include <QWidget>

class object : public QWidget
{
    Q_OBJECT
public:
    explicit object(QWidget *parent = nullptr);

signals:

};

#endif // OBJECT_H
