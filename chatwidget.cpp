#include "chatwidget.h"
#include "ui_chatwidget.h"

ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWidget)
{
    ui->setupUi(this);
    ui->chatTargetNameLabel->setText("");
}

ChatWidget::~ChatWidget()
{
    delete ui;
}

CustomWidget *ChatWidget::getTargetCustom() const
{
    return targetCustom;
}

void ChatWidget::setTargetCustom(CustomWidget *newTargetCustom)
{
    targetCustom = newTargetCustom;
}

void ChatWidget::targetCustomChanged(CustomWidget *newTargetCustom)
{
    this->targetCustom=newTargetCustom;
    if(targetCustom==nullptr)
    {
        ui->chatTargetNameLabel->setText("");
        //log部分
        //...
    }
    else
    {
        ui->chatTargetNameLabel->setText(targetCustom->getName());
        //log部分
        //...
    }

}
