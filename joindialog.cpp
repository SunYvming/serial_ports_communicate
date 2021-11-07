#include "joindialog.h"
#include "ui_joindialog.h"

#include <QDebug>

joinDialog::joinDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::joinDialog)
{
    ui->setupUi(this);
    ui->portErr->setStyleSheet("color:red;");
    ui->nameErr->setStyleSheet("color:red;");
    this->setFixedSize(360,560);
    connect(ui->portBox, SIGNAL(clicked()), this, SLOT(comboBox_clicked()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(pushButton_clicked()));
}

joinDialog::~joinDialog()
{
    delete ui;
}

void joinDialog::comboBox_clicked()
{
    ui->portBox->clear();
    if(!avilablePort.isEmpty())
        avilablePort.clear();

    avilablePort=QSerialPortInfo :: availablePorts();
    foreach(QSerialPortInfo info,avilablePort)
    {
        if(!(info.isBusy()||info.isNull()||!info.isValid()))
        {
            ui->portBox->addItem(info.portName());
        }
    }
}


void joinDialog::pushButton_clicked()
{
    bool wrong=false;
    if(ui->portBox->currentText()=="")
    {
        ui->portErr->setText("串口非法，请选择串口");
        wrong=true;
    }
    else
    {
        ui->portErr->setText("");
    }
    if(ui->userNameEdit->text()=="")
    {
        ui->nameErr->setText("名称非法，请输入名称");
        wrong=true;
    }
    else
    {
        ui->nameErr->setText("");
    }
    if(wrong)
        return;

    this->mainwindow=new MainWindow(this);
    if(!mainwindow->openSerialPort(ui->portBox->currentText()))
    {
        delete this->mainwindow;
        return;
    }
    mainwindow->show();
    this->hide();
}


