#include "customwidget.h"
#include "ui_customwidget.h"

CustomWidget::CustomWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomWidget)
{
    ui->setupUi(this);
    timer=new QTimer(this);
    timer->start(3000);

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
            emit targetCustomChanged(this);
        }
    }
    else active=false;
}


