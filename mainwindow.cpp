#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>
#include <QCloseEvent>

#include "coder.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    coder=new Coder();
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
    coder->decoder(serialCom->readAll());
}

void MainWindow::serial_receiveBeat(QString com,QString name,QString time)
{
    serialCom->write(Coder::encoder(Coder::Kind::Debug,this->serialCom->portName(),this->userName,nullptr,"Receive beat from "+com+":"+name+" at "+time));
}

void MainWindow::serial_writeData(const QByteArray &data)
{

}

void MainWindow::timer_timeOut()
{
    serialCom->write(Coder::encoder(Coder::Kind::Beat,this->serialCom->portName(),this->userName));
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
