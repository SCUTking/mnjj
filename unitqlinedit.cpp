#include "unitqlinedit.h"
#include <QLayout>
#include <QStyle>
UnitQLineEdit::UnitQLineEdit(QWidget* parent): QLineEdit(parent)
{
    m_unitButton = new QPushButton;
    //单位按钮扁平无边框
    m_unitButton->setStyleSheet("border-style:solid;");
    m_unitButton->setFlat(true);
    //单位加入布局
    QBoxLayout* layout = new QBoxLayout(QBoxLayout::LeftToRight);
    layout->addStretch();
    layout->setSpacing(0);
    //单位按钮的Margins
    layout->setContentsMargins(0, 0, 13, 0);
    layout->addWidget(m_unitButton);
    this->setLayout(layout);
}

UnitQLineEdit::~UnitQLineEdit()
{
}

QString UnitQLineEdit::UnitText() const
{
    return   this->m_unitButton->text();
}

void UnitQLineEdit::SetUnitText(const QString& unitText)
{
    if (unitText.isEmpty() || this->m_unitButton->text() == unitText)
    {
        return;
    }

    m_unitButton->setFont(this->font());
    this->m_unitButton->setText(unitText);
    // this->m_unitButton->setVisible(true);
    //自己改了一下
    int width = 60;//this->fontMetrics().width(m_unitButton->text());
    m_unitButton->setFixedWidth(width);
    //到单位开头了就往下显示，防止往后输入的内容有一部分在按钮下面
    QBoxLayout* layout = (QBoxLayout*)this->layout();
    QMargins margins = layout->contentsMargins();
    setTextMargins(margins.left(), margins.top(), width + margins.right(), margins.bottom());
}

