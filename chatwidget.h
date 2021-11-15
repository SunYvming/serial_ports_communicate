#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>

#include "customwidget.h"

namespace Ui {
class ChatWidget;
}

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWidget(QWidget *parent = nullptr);
    ~ChatWidget();

    CustomWidget *getTargetCustom() const;
    void setTargetCustom(CustomWidget *newTargetCustom);
public slots:
    void targetCustomChanged(CustomWidget *newTargetCustom);
    void sendButton_clicked();
    void listAppend(CustomWidget *target,log_t newLog);

signals:
    void writeData(QString com,QString name,QString time,QString body);
    void customSend(QString com,QString name,QString time,QString body);

protected:
    virtual void resizeEvent(QResizeEvent *event) override;


private:
    Ui::ChatWidget *ui;

    //ReadOnly!!!
    CustomWidget *targetCustom;
};

#endif // CHATWIDGET_H
