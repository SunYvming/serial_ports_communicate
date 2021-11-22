#include "chatwidget.h"
#include "ui_chatwidget.h"

#include <QTime>
#include <QDebug>
#include <QPainter>

#include <QMimeDatabase>
#include <QMimeData>

#include <QBuffer>
#include <QFile>

#include <QFileDialog>

#include "qnchatmessage.h"
#include "filemessage.h"

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
    connect(ui->fileButton,&QPushButton::clicked,this,&ChatWidget::fileButton_clicked);

    timer=new QTimer(this);
    timer->start(25);
    connect(this->timer,&QTimer::timeout,this,&ChatWidget::timer_timeout);

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
        if(QString(ui->logListWidget->itemWidget(ui->logListWidget->item(i))->metaObject()->className())=="QNChatMessage")
        {
            QNChatMessage* messageW = (QNChatMessage*)ui->logListWidget->itemWidget(ui->logListWidget->item(i));
            QListWidgetItem* item = ui->logListWidget->item(i);

            messageW->setFixedWidth(ui->logListWidget->width());
            QSize size = messageW->fontRect(messageW->text());
            item->setSizeHint(size);
            messageW->setText(messageW->text(), messageW->time(), size, messageW->userType());
            ui->logListWidget->setItemWidget(item, messageW);
        }
    }
    ui->logListWidget->setCurrentRow(ui->logListWidget->count()-1);
}


void ChatWidget::fileButton_clicked()
{
    if(this->targetCustom==nullptr)
        return;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "./",QString(tr("All (*.*)")));
    QFile *file=new QFile(fileName,this);
    if (!file->open(QIODevice::ReadOnly))
        return;
    QFileInfo fileInfo(*file);

    QString data=QString::fromUtf8(file->readAll().toBase64());

    QString name=fileInfo.fileName();

    int length=data.length();

    file_to_emit_t newFile;
    newFile.signalQueue.clear();
    for(int i=1;i<=(length/3000)+1;i++)
    {
        signal_to_emit_t newSignal;
        newSignal.com=this->targetCustom->getCom();
        newSignal.name=this->targetCustom->getName();
        newSignal.time=QDateTime::currentDateTimeUtc().toTime_t();
        newSignal.body=data.left(3000);
        data.remove(0,3000);
        newSignal.number=i;
        newSignal.total=(length/3000)+1;
        newSignal.fileName=name;
        newFile.signalQueue.enqueue(newSignal);
    }
    //
    newFile.isAccept=true;
    //
    file_to_emit_list.append(newFile);

    emit customSend(this->targetCustom->getCom(),this->targetCustom->getName(),QString::number(QDateTime::currentDateTimeUtc().toTime_t()),name);

    FileMessage* message = new FileMessage(ui->logListWidget);
    QListWidgetItem* item = new QListWidgetItem(ui->logListWidget);
    item->setSizeHint(QSize(ui->logListWidget->width(),100));
    message->setPairItem(item);
    message->setFileName(name);
    message->setTotal((length/3000)+1);
    message->setIsSender(true);
    message->setParentWidget(ui->logListWidget);
    connect(this,&ChatWidget::progressChanged,message,&FileMessage::progressUpdate);
    ui->logListWidget->setItemWidget(item, message);
    ui->logListWidget->setCurrentRow(ui->logListWidget->count()-1);

    file->close();
    delete file;
}

void ChatWidget::timer_timeout()
{
    if(!file_to_emit_list.isEmpty())
    {
        for(int i=0;i<file_to_emit_list.length();)
        {
            file_to_emit_t tempFile=file_to_emit_list.at(i);
            if(tempFile.isAccept==true)
            {
                while(!tempFile.signalQueue.isEmpty())
                {
                    signal_to_emit.enqueue(tempFile.signalQueue.dequeue());
                }
                file_to_emit_list.removeAt(i);
            }
            else i++;
        }
    }


    if(!signal_to_emit.isEmpty())
    {
        signal_to_emit_t newSignal=signal_to_emit.dequeue();
        emit writeFile(newSignal.com,newSignal.name,newSignal.time,newSignal.body,newSignal.fileName,newSignal.number,newSignal.total);
        emit progressChanged(newSignal.fileName,newSignal.number,newSignal.total);
    }
}

