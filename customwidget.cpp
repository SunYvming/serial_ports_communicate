#include "customwidget.h"
#include "ui_customwidget.h"

#include "mainwindow.h"

#include <QPainter>


CustomWidget::CustomWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomWidget)
{
    ui->setupUi(this);
    timer=new QTimer(this);
    timer->start(10000);

    active=false;

    connect(timer,&QTimer::timeout,this,[this]{emit customDisconnect();});
    connect(this,&CustomWidget::nameChanged,ui->nameLabel,[this](){ui->nameLabel->setText(name);});
}

CustomWidget::~CustomWidget()
{
    if(active)
        emit targetCustomChanged(nullptr);
    delete timer;
    delete ui;
}

const QString &CustomWidget::getName() const
{
    return name;
}

void CustomWidget::setName(const QString &newName)
{
    if(name!=newName)
    {
        name = newName;
        emit nameChanged();
    }
    QPixmap pixmap=QPixmap(50,50);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setBrush(QBrush(QColor(75,164,242)));
    painter.setPen(Qt::white);
    painter.drawEllipse(0,0,50,50);
    painter.setPen(Qt::black);
    painter.setFont(QFont("MicrosoftYaHei",15));
    painter.drawText(pixmap.rect(), Qt::AlignCenter, name);
    ui->cusIcon->setPixmap(pixmap);
}

const QString &CustomWidget::getCom() const
{
    return com;
}

void CustomWidget::setCom(const QString &newCom)
{
    com = newCom;
}

QListWidgetItem *CustomWidget::getLinkItem() const
{
    return linkItem;
}

void CustomWidget::setLinkItem(QListWidgetItem *newLinkItem)
{
    linkItem = newLinkItem;
}

bool CustomWidget::ifActive() const
{
    return active;
}

void CustomWidget::selectChanged(QListWidgetItem *item)
{
    if(this->linkItem==item)
    {
        if(active)
        {
            //do nothing
        }
        else
        {
            active=true;
            unreadCounter=0;
            QPixmap pixmap=QPixmap(25,25);
            pixmap.fill(Qt::transparent);
            ui->countIcon->setPixmap(pixmap);
            emit unreadChanged();
            emit targetCustomChanged(this);
        }
    }
    else active=false;
}

void CustomWidget::getNewLog(log_t newLog)
{
    if((newLog.senderCom==com&&newLog.senderName==name&&newLog.receiverCom==thisCom&&newLog.receiverName==thisName)||
       (newLog.receiverCom==com&&newLog.receiverName==name&&newLog.senderCom==thisCom&&newLog.senderName==thisName))
    {
        this->log.append(newLog);
        emit logAppend(this,newLog);
        if(!active)
        {
            unreadCounter++;
            QPixmap pixmap=QPixmap(25,25);
            pixmap.fill(Qt::transparent);
            QPainter painter(&pixmap);
            painter.setBrush(Qt::red);
            painter.setPen(Qt::white);
            painter.drawEllipse(0,0,25,25);
            painter.setPen(Qt::black);
            painter.setFont(QFont("MicrosoftYaHei",10));
            painter.drawText(pixmap.rect(), Qt::AlignCenter, QString::number(unreadCounter));
            ui->countIcon->setPixmap(pixmap);

            emit unreadChanged();
        }
    }
}

const QString &CustomWidget::getThisCom() const
{
    return thisCom;
}

const QString &CustomWidget::getThisName() const
{
    return thisName;
}

void CustomWidget::setThisCom(const QString &newThisCom)
{
    thisCom = newThisCom;
}

void CustomWidget::setThisName(const QString &newThisName)
{
    thisName = newThisName;
}


