#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QTimer>

#include <QListWidgetItem>

namespace Ui {
class CustomWidget;
}

typedef struct
{
    QString senderCom;
    QString senderName;
    QString receiverCom;
    QString receiverName;
    QString time;
    QString body;
}log_t;

class CustomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CustomWidget(QWidget *parent = nullptr);
    ~CustomWidget();

    const QString &getName() const;
    void setName(const QString &newName);

    const QString &getCom() const;
    void setCom(const QString &newCom);

    QListWidgetItem *getLinkItem() const;
    void setLinkItem(QListWidgetItem *newLinkItem);

    bool ifActive() const;

    QList<log_t> log;

    void setThisName(const QString &newThisName);

    void setThisCom(const QString &newThisCom);

public slots:
    void restartTimer(QString com)
    {
        if(this->com==com)
            if(timer!=nullptr)
            {
                timer->setInterval(3000);
            }
    }

    void selectChanged(QListWidgetItem *item);
    void getNewLog(log_t newLog);


signals:
    void nameChanged();
    void customDisconnect();
    void targetCustomChanged(CustomWidget* targetCustom);
    void logAppend(CustomWidget *custom,log_t newLog);



private:
    Ui::CustomWidget *ui;
    QString name;
    QString com;
    QTimer *timer;

    QString thisName;
    QString thisCom;

    bool active;
    //Read Only!!!
    QListWidgetItem *linkItem;

};

#endif // CUSTOMWIDGET_H
