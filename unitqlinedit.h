#ifndef UNITQLINEDIT_H
#define UNITQLINEDIT_H
#include <QLineEdit>
#include <QPushButton>

class UnitQLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    UnitQLineEdit(QWidget* parent = Q_NULLPTR);
    ~UnitQLineEdit();
    //获取编辑框单位
    QString UnitText()const;

    //设置编辑框单位
    void SetUnitText(const QString& unitText);

private:
    QPushButton* m_unitButton = nullptr;//单位文本按钮
};


#endif // UNITQLINEDIT_H
