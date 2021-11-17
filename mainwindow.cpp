#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>
#include <QCloseEvent>

#include "coder.h"
#include "customwidget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    coder=new Coder();
    this->resize(QSize(1000,600));
    ui->splitter->setStretchFactor(0,4);
    ui->splitter->setStretchFactor(1,6);
    ui->customList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->customList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(ui->customList,&QListWidget::itemClicked,this,&MainWindow::customList_itemClicked);
    connect(coder,&Coder::coder_receiveMessage,this,&MainWindow::customMessageRead);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::openSerialPort(QString portName)
{
    serialCom=new QSerialPort(portName,this);
    serialCom->setPortName(portName);
    serialCom->setBaudRate(QSerialPort::Baud115200);
    serialCom->setDataBits(QSerialPort::Data8);
    serialCom->setParity(QSerialPort::NoParity);
    serialCom->setStopBits(QSerialPort::OneStop);
    serialCom->setFlowControl(QSerialPort::NoFlowControl);


    if(serialCom->open(QSerialPort::ReadWrite))
    {
        connect(serialCom, &QSerialPort::readyRead, this, &MainWindow::serial_readData);
        connect(coder,&Coder::coder_receiveBeat,this,&MainWindow::serial_receiveBeat);
        connect(ui->chatWidget,&ChatWidget::writeData,this,&MainWindow::serial_writeData);
        connect(ui->chatWidget,&ChatWidget::writeFile,this,&MainWindow::serial_writeFile);
        connect(ui->chatWidget,&ChatWidget::customSend,this,&MainWindow::customMessageSend);

        timer=new QTimer(this);
        connect(timer, &QTimer::timeout, this,&MainWindow::timer_timeOut);
        timer->start(1000);
        return true;
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), "Open error");
        return false;
    }
}

const QString &MainWindow::getUserName() const
{
    return userName;
}

void MainWindow::setUserName(const QString &newUserName)
{
    userName = newUserName;
}

void MainWindow::serial_readData()
{

    QByteArray buf=serialCom->readAll();

        QByteArray buf_before;
        QByteArray buf_after;

        if(buf.contains(QString("$").toLatin1())&&buf.contains(QString("#").toLatin1()))
        {
            if(buf.indexOf('#')<buf.indexOf('$'))
            {
                buffer.clear();
                buf.remove(0,buf.indexOf('#')+1);
                buffer.append(buf.left(buf.indexOf('$')));
                coder->decoder(buffer);
                buffer.clear();
                flag=false;
            }
            else
            {
                buf_before.append(buf.left(buf.indexOf('$')));
                buf_after.append(buf.right(buf.length()-buf.indexOf('#')-1));
                if(flag)
                {
                    buffer.append(buf_before);
                    coder->decoder(buffer);
                    buffer.clear();
                    buffer.append(buf_after);
                }
                else
                {
                    buffer.clear();
                    buffer.append(buf_after);
                    flag=true;
                }
            }
        }
        else if(buf.contains(QString("$").toLatin1()))
        {
            if(flag)
            {
                buffer.append(buf.left(buf.indexOf('$')));
                coder->decoder(buffer);
                buffer.clear();
                flag=false;
            }
            else
            {
                buffer.clear();
            }
        }
        else if(buf.contains(QString("#").toLatin1()))
        {
            buffer.clear();
            flag=true;
            buffer.append(buf.right(buf.length()-buf.indexOf('#')-1));
        }
        else
        {
            if(flag)
                buffer.append(buf);
            else
                buffer.clear();
        }
}

void MainWindow::serial_writeData(QString com,QString name,QString time,QString body)
{
    QByteArray data=Coder::encoder(Coder::Kind::Message,this->serialCom->portName(),this->getUserName(),com,name,body);
    serialCom->write(QString('#').toLatin1());
    serialCom->write(data);
    serialCom->write(QString('$').toLatin1());
}

void MainWindow::serial_writeFile(QString com,QString name,QString time,QString body,QString Filename,int number,int count)
{
    QByteArray data=Coder::encoder(Coder::Kind::File,this->serialCom->portName(),this->getUserName(),com,name,body,Filename,number,count);
    serialCom->write(QString('#').toLatin1());
    serialCom->write(data);
    serialCom->write(QString('$').toLatin1());
}

void MainWindow::serial_receiveBeat(QString com,QString name,QString time)
{
    //serialCom->write(Coder::encoder(Coder::Kind::Debug,this->serialCom->portName(),this->userName,nullptr,"Receive beat from "+com+":"+name+" at "+time));
    emit customBeat(com);
    foreach(CustomWidget *t,customs)
    {
        if(t->getCom()==com)
        {
            t->setName(name);
            return;
        }
    }

    CustomWidget *w = new CustomWidget(this);
    w->setCom(com);
    w->setName(name);
    w->setThisCom(serialCom->portName());
    w->setThisName(getUserName());
    customs.append(w);
    QListWidgetItem *item=new QListWidgetItem(ui->customList,0);
    item->setSizeHint(QSize(180, 50));
    ui->customList->addItem(item);
    ui->customList->setItemWidget(item,w);
    w->setLinkItem(item);
    w->show();
    connect(this,&MainWindow::customBeat,w,&CustomWidget::restartTimer);
    connect(this,&MainWindow::customMessageWrite,w,&CustomWidget::getNewLog);
    connect(this,&MainWindow::customMessageRead,w,&CustomWidget::getNewLog);
    connect(this,&MainWindow::customChanged,w,&CustomWidget::selectChanged);
    connect(w,&CustomWidget::targetCustomChanged,ui->chatWidget,&ChatWidget::targetCustomChanged);
    connect(w,&CustomWidget::logAppend,ui->chatWidget,&ChatWidget::listAppend);
    connect(w,&CustomWidget::customDisconnect,this,[this,w,item]{
        customs.removeOne(w);
        delete w;
        ui->customList->removeItemWidget(item);
        delete item;
    });
    connect(w,&CustomWidget::unreadChanged,this,[this]{
        ui->customList->update();
    });
    connect(w,&CustomWidget::nameChanged,this,[this]{
         ui->customList->update();
    });
}

void MainWindow::timer_timeOut()
{
    if(!block)
    {
        serialCom->write(QString('#').toLatin1());
        serialCom->write(Coder::encoder(Coder::Kind::Beat,this->serialCom->portName(),this->userName));
        serialCom->write(QString('$').toLatin1());
    }
}

void MainWindow::closeEvent ( QCloseEvent * event )
{
    if(serialCom!=nullptr)
    {
        if(serialCom->isOpen())
            serialCom->close();
        delete serialCom;
    }
    if(timer!=nullptr)
    {
        if(timer->isActive())
            timer->stop();
        delete timer;
    }
    event->accept();
}

void MainWindow::customList_itemClicked(QListWidgetItem *item)
{
    emit customChanged(item);
}

void MainWindow::customMessageSend(QString com, QString name, QString time, QString body)
{
    static log_t newLog;
    newLog.senderCom=this->serialCom->portName();
    newLog.senderName=this->getUserName();
    newLog.receiverCom=com;
    newLog.receiverName=name;
    newLog.time=time;
    newLog.body=body;

    emit customMessageWrite(newLog);
}

