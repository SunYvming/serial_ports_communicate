#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QTimer>

#include <QListWidgetItem>

namespace Ui {
class CustomWidget;
}

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

signals:
    void nameChanged();
    void customDisconnect();
    void widgetActive();
    void targetCustomChanged(CustomWidget* targetCustom);



private:
    Ui::CustomWidget *ui;
    QString name;
    QString com;
    QTimer *timer;

    bool active;
    //Read Only!!!
    QListWidgetItem *linkItem;
    //log
};

#endif // CUSTOMWIDGET_H
