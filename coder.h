#ifndef CODER_H
#define CODER_H

#include <QObject>
#include <QSerialPortInfo>
#include <QSerialPort>

#include "customwidget.h"

class Coder:public QObject
{
    Q_OBJECT
public:

    enum class Kind
    {
        Beat,
        Message,
        Debug,
        File
    };
    Q_ENUM(Kind)

    Coder();
    static QByteArray encoder(Kind kind,QString senderCom=nullptr,QString senderName=nullptr,QString receiverCom=nullptr,QString receiverName=nullptr,QString body=nullptr,QString fileName=nullptr);
    void decoder(QByteArray input,QString thisname=nullptr);

signals:
    void coder_receiveBeat(QString com,QString name,QString time);
    void coder_receiveMessage(log_t newLog);
};

#endif // CODER_H
