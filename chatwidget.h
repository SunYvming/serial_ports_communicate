#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QQueue>

#include "customwidget.h"
#include "filemessage.h"

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

    typedef struct
    {
        QQueue<signal_to_emit_t> signalQueue;
        bool isAccept;
    }file_to_emit_t;

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
    void receiveFile(QString fileName,QString sender,int number,int count);

signals:
    void writeData(QString com,QString name,QString time,QString body);
    void writeFile(QString com,QString name,QString time,QString body,QString fileName,int number,int total);
    void customSend(QString com,QString name,QString time,QString body);
    void progressChanged(QString fileName,int number,int total);
    void progressFinish(QString fileName,QString dir);

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    Ui::ChatWidget *ui;

    //ReadOnly!!!
    CustomWidget *targetCustom;
    QQueue<signal_to_emit_t> signal_to_emit;
    QList<file_to_emit_t> file_to_emit_list;
    QTimer *timer;
    QList<QString> keeper;
};

#endif // CHATWIDGET_H
