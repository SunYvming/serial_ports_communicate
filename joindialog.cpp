#include "joindialog.h"
#include "ui_joindialog.h"

#include <QDebug>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

joinDialog::joinDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::joinDialog)
{
    ui->setupUi(this);
    ui->portErr->setStyleSheet("color:red;");
    ui->nameErr->setStyleSheet("color:red;");
    ui->pushButton_2->setFlat(true);
    this->setWindowFlags(Qt::FramelessWindowHint);
    connect(ui->portBox, SIGNAL(clicked()), this, SLOT(comboBox_clicked()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(pushButton_clicked()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(pushButton_2_clicked()));
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

    this->mainwindow=new MainWindow();
    if(!mainwindow->openSerialPort(ui->portBox->currentText()))
    {
        delete this->mainwindow;
        return;
    }
    mainwindow->setUserName(ui->userNameEdit->text());

    QPropertyAnimation *pScaleAnimation1 = new QPropertyAnimation(this, "geometry");
    pScaleAnimation1->setDuration(200);
    pScaleAnimation1->setStartValue(this->geometry());
    pScaleAnimation1->setEndValue(QRect(this->geometry().topLeft(), QSize(0,this->size().height())));
    pScaleAnimation1->start();
    connect(pScaleAnimation1,&QPropertyAnimation::finished,pScaleAnimation1,[pScaleAnimation1,this]{
        this->hide();
        mainwindow->show();
        delete pScaleAnimation1;
    });

}

void joinDialog::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bDrag = true;
        mouseStartPoint = event->globalPos();
        windowTopLeftPoint = this->frameGeometry().topLeft();
    }
}

void joinDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bDrag)
    {
        QPoint distance = event->globalPos() - mouseStartPoint;
        this->move(windowTopLeftPoint + distance);
    }
}

void joinDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bDrag = false;
    }
}



void joinDialog::pushButton_2_clicked()
{
    QPropertyAnimation *pScaleAnimation1 = new QPropertyAnimation(this, "geometry");
    pScaleAnimation1->setDuration(200);
    pScaleAnimation1->setStartValue(this->geometry());
    pScaleAnimation1->setEndValue(QRect(this->geometry().topLeft(), QSize(this->size().width(),0)));
    pScaleAnimation1->start();
    connect(pScaleAnimation1,&QPropertyAnimation::finished,pScaleAnimation1,[pScaleAnimation1,this]{
        this->close();
        delete pScaleAnimation1;
    });
}

