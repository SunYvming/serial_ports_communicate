#include "chatwidget.h"
#include "ui_chatwidget.h"

#include <QTime>
#include <QDebug>

ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWidget)
{
    ui->setupUi(this);
    ui->chatTargetNameLabel->setText("");
    this->targetCustom=nullptr;
    connect(ui->sendButton,&QPushButton::clicked,this,&ChatWidget::sendButton_clicked);
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
        ui->logListWidget->clear();
    }
    else
    {
        ui->chatTargetNameLabel->setText(targetCustom->getName());
        ui->logListWidget->clear();
        //reload
        foreach(log_t t,this->targetCustom->log)
        {
            ui->logListWidget->addItem(t.time+"::"+t.senderName+"->"+t.receiverName+":"+t.body);
        }
    }

}

void ChatWidget::sendButton_clicked()
{
    if(this->targetCustom!=nullptr)
    {
        emit customSend(this->targetCustom->getCom(),this->targetCustom->getName(),QString::number(QDateTime::currentDateTimeUtc().toTime_t()),ui->textEdit->toPlainText());
        emit writeData(this->targetCustom->getCom(),this->targetCustom->getName(),QString::number(QDateTime::currentDateTimeUtc().toTime_t()),ui->textEdit->toPlainText());
    }
}

void ChatWidget::listAppend(CustomWidget *target, log_t newLog)
{
    //可美化
    if(target==this->targetCustom)
        ui->logListWidget->addItem(newLog.time+"::"+newLog.senderName+"->"+newLog.receiverName+":"+newLog.body);
}

