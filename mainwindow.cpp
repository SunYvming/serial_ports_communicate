#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
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

void MainWindow::serial_readData()
{
    serialCom->write(serialCom->readAll());
}

void MainWindow::serial_writeData(const QByteArray &data)
{

}

void MainWindow::timer_timeOut()
{
    serialCom->write("beat");
}
