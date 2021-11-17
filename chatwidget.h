#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QQueue>

#include "customwidget.h"

namespace Ui {
class ChatWidget;
}

class ChatWidget : public QWidget
{
    Q_OBJECT

    typedef struct
    {
        QString com;
        QString name;
        QString time;
        QString body;
        QString fileName;
        int number;
        int total;
    }signal_to_emit_t;

public:
    explicit ChatWidget(QWidget *parent = nullptr);
    ~ChatWidget();

    CustomWidget *getTargetCustom() const;
    void setTargetCustom(CustomWidget *newTargetCustom);
public slots:
    void targetCustomChanged(CustomWidget *newTargetCustom);
    void sendButton_clicked();
    void listAppend(CustomWidget *target,log_t newLog);
    void fileButton_clicked();
    void timer_timeout();

signals:
    void writeData(QString com,QString name,QString time,QString body);
    void writeFile(QString com,QString name,QString time,QString body,QString fileName,int number,int total);
    void customSend(QString com,QString name,QString time,QString body);

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    Ui::ChatWidget *ui;

    //ReadOnly!!!
    CustomWidget *targetCustom;
    QQueue<signal_to_emit_t> signal_to_emit;
    QTimer *timer;
};

#endif // CHATWIDGET_H
