#include "chatwidget.h"
#include "ui_chatwidget.h"

#include <QTime>
#include <QDebug>
#include <QPainter>

#include "qnchatmessage.h"

ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWidget)
{
    ui->setupUi(this);
    ui->chatTargetNameLabel->setText("");
    ui->logListWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->logListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->logListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->splitter->setStretchFactor(0,8);
    ui->splitter->setStretchFactor(1,2);
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
        int i=0;
        //reload
        foreach(log_t t,this->targetCustom->log)
        {
            int lastTime;
            if(i==0)
                lastTime=0;
            else
                lastTime=this->targetCustom->log.at(i-1).time.toInt();
            i++;
            int newTime=t.time.toInt();
            if(newTime-lastTime>=60)
            {
                QNChatMessage* messageTime = new QNChatMessage(ui->logListWidget->parentWidget());
                QListWidgetItem* itemTime = new QListWidgetItem(ui->logListWidget);

                QSize size = QSize(ui->logListWidget->width(), 40);
                messageTime->resize(size);
                itemTime->setSizeHint(size);
                messageTime->setText(t.time, t.time, size, QNChatMessage::User_Time);
                ui->logListWidget->setItemWidget(itemTime, messageTime);
            }

            QNChatMessage* messageW = new QNChatMessage(ui->logListWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->logListWidget);

            QPixmap rpixmap=QPixmap(100,100);
            rpixmap.fill();
            QPainter rpainter(&rpixmap);
            rpainter.setBrush(QBrush(QColor(75,164,242)));
            rpainter.setPen(Qt::white);
            rpainter.drawEllipse(0,0,100,100);
            rpainter.setPen(Qt::black);
            rpainter.setFont(QFont("MicrosoftYaHei",30));
            rpainter.drawText(rpixmap.rect(), Qt::AlignCenter, this->targetCustom->getThisName());
            messageW->setRightPixmap(rpixmap);

            QPixmap lpixmap=QPixmap(100,100);
            lpixmap.fill();
            QPainter lpainter(&lpixmap);
            lpainter.setBrush(QBrush(QColor(75,164,242)));
            lpainter.setPen(Qt::white);
            lpainter.drawEllipse(0,0,100,100);
            lpainter.setPen(Qt::black);
            lpainter.setFont(QFont("MicrosoftYaHei",30));
            lpainter.drawText(lpixmap.rect(), Qt::AlignCenter, this->targetCustom->getName());
            messageW->setLeftPixmap(lpixmap);

            messageW->setFixedWidth(ui->logListWidget->width());
            QSize size = messageW->fontRect(t.body);
            item->setSizeHint(size);
            if(t.senderCom==this->targetCustom->getThisCom()&&t.senderName==this->targetCustom->getThisName())
                messageW->setText(t.body, t.time, size, QNChatMessage::User_Me);
            else if(t.receiverCom==this->targetCustom->getThisCom()&&t.receiverName==this->targetCustom->getThisName())
                messageW->setText(t.body, t.time, size, QNChatMessage::User_She);
            ui->logListWidget->setItemWidget(item, messageW);
            ui->logListWidget->setCurrentRow(ui->logListWidget->count()-1);
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
    if(target==this->targetCustom)
    {

        int lastTime;
        if(this->targetCustom->log.count()>1)
            lastTime=this->targetCustom->log.at(this->targetCustom->log.count()-2).time.toInt();
        else
            lastTime=0;
        int newTime=newLog.time.toInt();
        if(newTime-lastTime>=60)
        {
            QNChatMessage* messageTime = new QNChatMessage(ui->logListWidget->parentWidget());
            QListWidgetItem* itemTime = new QListWidgetItem(ui->logListWidget);

            QSize size = QSize(this->width(), 40);
            messageTime->resize(size);
            itemTime->setSizeHint(size);
            messageTime->setText(newLog.time, newLog.time, size, QNChatMessage::User_Time);
            ui->logListWidget->setItemWidget(itemTime, messageTime);
        }

        QNChatMessage* messageW = new QNChatMessage(ui->logListWidget->parentWidget());
        QListWidgetItem* item = new QListWidgetItem(ui->logListWidget);

        QPixmap rpixmap=QPixmap(100,100);
        rpixmap.fill();
        QPainter rpainter(&rpixmap);
        rpainter.setBrush(QBrush(QColor(75,164,242)));
        rpainter.setPen(Qt::white);
        rpainter.drawEllipse(0,0,100,100);
        rpainter.setPen(Qt::black);
        rpainter.setFont(QFont("MicrosoftYaHei",30));
        rpainter.drawText(rpixmap.rect(), Qt::AlignCenter, this->targetCustom->getThisName());
        messageW->setRightPixmap(rpixmap);

        QPixmap lpixmap=QPixmap(100,100);
        lpixmap.fill();
        QPainter lpainter(&lpixmap);
        lpainter.setBrush(QBrush(QColor(75,164,242)));
        lpainter.setPen(Qt::white);
        lpainter.drawEllipse(0,0,100,100);
        lpainter.setPen(Qt::black);
        lpainter.setFont(QFont("MicrosoftYaHei",30));
        lpainter.drawText(lpixmap.rect(), Qt::AlignCenter, this->targetCustom->getName());
        messageW->setLeftPixmap(lpixmap);

        messageW->setFixedWidth(ui->logListWidget->width());
        QSize size = messageW->fontRect(newLog.body);
        item->setSizeHint(size);
        if(newLog.senderCom==this->targetCustom->getThisCom()&&newLog.senderName==this->targetCustom->getThisName())
            messageW->setText(newLog.body, newLog.time, size, QNChatMessage::User_Me);
        else if(newLog.receiverCom==this->targetCustom->getThisCom()&&newLog.receiverName==this->targetCustom->getThisName())
            messageW->setText(newLog.body, newLog.time, size, QNChatMessage::User_She);
        ui->logListWidget->setItemWidget(item, messageW);
        ui->logListWidget->setCurrentRow(ui->logListWidget->count()-1);
    }
}

void ChatWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    for(int i = 0; i < ui->logListWidget->count(); i++)
    {
        QNChatMessage* messageW = (QNChatMessage*)ui->logListWidget->itemWidget(ui->logListWidget->item(i));
        QListWidgetItem* item = ui->logListWidget->item(i);

        messageW->setFixedWidth(ui->logListWidget->width());
        QSize size = messageW->fontRect(messageW->text());
        item->setSizeHint(size);
        messageW->setText(messageW->text(), messageW->time(), size, messageW->userType());
        ui->logListWidget->setItemWidget(item, messageW);
    }
    ui->logListWidget->setCurrentRow(ui->logListWidget->count()-1);
}

