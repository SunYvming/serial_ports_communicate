#include "coder.h"

#include <QVariant>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonValue>

#include <QMetaEnum>

#include <QTime>
#include <QDebug>
#include <QTextCodec>
#include <QFile>
#include <QDir>
#include <QMimeDatabase>
#include <QBuffer>
#include <QImageReader>

#include "customwidget.h"

Coder::Coder()
{

}

QByteArray Coder::encoder(Kind kind,QString senderCom,QString senderName,QString receiverCom,QString receiverName,QString body,QString fileName)
{
    switch (kind)
    {
        case Kind::Beat:
        {
            QJsonObject senderObject;
            senderObject.insert("Com",senderCom);
            senderObject.insert("Name",senderName);

            QJsonObject bodyObject;
            bodyObject.insert("Time",QString::number(QDateTime::currentDateTimeUtc().toTime_t()));
            bodyObject.insert("Data","no data");

            QJsonObject object;
            object.insert("Kind",QVariant::fromValue(kind).toString());
            object.insert("Sender",senderObject);
            object.insert("Body",bodyObject);

            QJsonDocument document;
            document.setObject(object);
            return document.toJson(QJsonDocument::Indented);

        }break;
        case Kind::Message:
        {
            QJsonObject senderObject;
            senderObject.insert("Com",senderCom);
            senderObject.insert("Name",senderName);

            QJsonObject receiveObject;
            receiveObject.insert("Com",receiverCom);
            receiveObject.insert("Name",receiverName);

            QJsonObject bodyObject;
            bodyObject.insert("Time",QString::number(QDateTime::currentDateTimeUtc().toTime_t()));
            bodyObject.insert("Data",body);

            QJsonObject object;
            object.insert("Kind",QVariant::fromValue(kind).toString());
            object.insert("Sender",senderObject);
            object.insert("Receiver",receiveObject);
            object.insert("Body",bodyObject);

            QJsonDocument document;
            document.setObject(object);
            return document.toJson(QJsonDocument::Indented);

        }break;
        case Kind::Debug:
        {
            QJsonObject senderObject;
            senderObject.insert("Com",senderCom);
            senderObject.insert("Name",senderName);

            QJsonObject bodyObject;
            bodyObject.insert("Time",QDateTime::currentDateTime().toString("hh:mm:ss:zzz"));
            bodyObject.insert("Data",body);

            QJsonObject object;
            object.insert("Kind",QVariant::fromValue(kind).toString());
            object.insert("Sender",senderObject);
            object.insert("Body",bodyObject);

            QJsonDocument document;
            document.setObject(object);
            return document.toJson(QJsonDocument::Indented);
        }break;
        case Kind::File:
        {
            QJsonObject senderObject;
            senderObject.insert("Com",senderCom);
            senderObject.insert("Name",senderName);

            QJsonObject receiveObject;
            receiveObject.insert("Com",receiverCom);
            receiveObject.insert("Name",receiverName);

            QJsonObject bodyObject;
            bodyObject.insert("Time",QString::number(QDateTime::currentDateTimeUtc().toTime_t()));
            bodyObject.insert("FileName",fileName);
            bodyObject.insert("Data",body);

            QJsonObject object;
            object.insert("Kind",QVariant::fromValue(kind).toString());
            object.insert("Sender",senderObject);
            object.insert("Receiver",receiveObject);
            object.insert("Body",bodyObject);

            QJsonDocument document;
            document.setObject(object);
            return document.toJson(QJsonDocument::Indented);
        }break;
    }
    return nullptr;
}

void Coder::decoder(QByteArray input,QString thisName)
{
    QString senderCom;
    QString senderName;
    QString receiverName;
    QString receiverCom;
    QString time;
    QString body;
    QString fileName;
    QFile *file;
    QDir *dir;
    static log_t newLog;

    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(input,&jsonError);
    if(jsonError.error!=0)
        qDebug()<<jsonError.error;
    if(!document.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        if(document.isObject())
        {
            QJsonObject object = document.object();
            if(object.contains("Kind"))
                if(object.value("Kind").isString())
                    switch (Kind(QMetaEnum::fromType<Coder::Kind>().keysToValue(object.value("Kind").toString().toLatin1())))
                    {
                        case Kind::Beat:
                        {
                            if(object.contains("Sender"))
                                if(object.value("Sender").isObject())
                                {
                                    QJsonObject senderObject=object.value("Sender").toObject();
                                    if(senderObject.contains("Com")&&senderObject.contains("Name"))
                                        if(senderObject.value("Com").isString()&&senderObject.value("Name").isString())
                                        {
                                            senderCom=senderObject.value("Com").toString();
                                            senderName=senderObject.value("Name").toString();

                                        }
                                        else return;
                                    else return;
                                }
                                else return;
                            else return;
                            if(object.contains("Body"))
                                if(object.value("Body").isObject())
                                {
                                    QJsonObject bodyObject=object.value("Body").toObject();
                                    if(bodyObject.contains("Time"))
                                        if(bodyObject.value("Time").isString())
                                            time=bodyObject.value("Time").toString();
                                        else return;
                                    else return;
                                }
                                else return;
                            else {return;}
                            emit coder_receiveBeat(senderCom,senderName,time);
                        }
                        case Kind::Message:
                        {
                            if(object.contains("Sender"))
                                if(object.value("Sender").isObject())
                                {
                                    QJsonObject senderObject=object.value("Sender").toObject();
                                    if(senderObject.contains("Com")&&senderObject.contains("Name"))
                                        if(senderObject.value("Com").isString()&&senderObject.value("Name").isString())
                                        {
                                            senderCom=senderObject.value("Com").toString();
                                            senderName=senderObject.value("Name").toString();
                                        }
                                        else return;
                                    else return;
                                }
                                else return;
                            else return;
                            if(object.contains("Receiver"))
                                if(object.value("Receiver").isObject())
                                {
                                    QJsonObject receiverObject=object.value("Receiver").toObject();
                                    if(receiverObject.contains("Com")&&receiverObject.contains("Name"))
                                        if(receiverObject.value("Com").isString()&&receiverObject.value("Name").isString())
                                        {
                                            receiverCom=receiverObject.value("Com").toString();
                                            receiverName=receiverObject.value("Name").toString();
                                        }
                                        else return;
                                    else return;
                                }
                                else return;
                            else return;
                            if(object.contains("Body"))
                                if(object.value("Body").isObject())
                                {
                                    QJsonObject bodyObject=object.value("Body").toObject();
                                    if(bodyObject.contains("Time")&&bodyObject.contains("Data"))
                                        if(bodyObject.value("Time").isString()&&bodyObject.value("Data").isString())
                                        {
                                            time=bodyObject.value("Time").toString();
                                            body=bodyObject.value("Data").toString();
                                        }
                                        else return;
                                    else return;
                                }
                                else return;
                            else {return;}
                            newLog.senderCom=senderCom;
                            newLog.senderName=senderName;
                            newLog.receiverCom=receiverCom;
                            newLog.receiverName=receiverName;
                            newLog.time=time;
                            newLog.body=body;
                            emit coder_receiveMessage(newLog);
                        }break;
                        case Kind::File:
                        {
                            if(object.contains("Sender"))
                                if(object.value("Sender").isObject())
                                {
                                    QJsonObject senderObject=object.value("Sender").toObject();
                                    if(senderObject.contains("Com")&&senderObject.contains("Name"))
                                        if(senderObject.value("Com").isString()&&senderObject.value("Name").isString())
                                        {
                                            senderCom=senderObject.value("Com").toString();
                                            senderName=senderObject.value("Name").toString();
                                        }
                                        else return;
                                    else return;
                                }
                                else return;
                            else return;
                            if(object.contains("Receiver"))
                                if(object.value("Receiver").isObject())
                                {
                                    QJsonObject receiverObject=object.value("Receiver").toObject();
                                    if(receiverObject.contains("Com")&&receiverObject.contains("Name"))
                                        if(receiverObject.value("Com").isString()&&receiverObject.value("Name").isString())
                                        {
                                            receiverCom=receiverObject.value("Com").toString();
                                            receiverName=receiverObject.value("Name").toString();
                                        }
                                        else return;
                                    else return;
                                }
                                else return;
                            else return;
                            if(object.contains("Body"))
                                if(object.value("Body").isObject())
                                {
                                    QJsonObject bodyObject=object.value("Body").toObject();
                                    if(bodyObject.contains("Time")&&bodyObject.contains("Data")&&bodyObject.contains("FileName"))
                                        if(bodyObject.value("Time").isString()&&bodyObject.value("Data").isString()&&bodyObject.value("FileName").isString())
                                        {
                                            time=bodyObject.value("Time").toString();
                                            fileName=bodyObject.value("FileName").toString();
                                            body=bodyObject.value("Data").toString();
                                            if(receiverName==thisName)
                                            {
                                                dir=new QDir;
                                                if(!dir->exists("./"+thisName))
                                                {
                                                    dir->mkdir("./"+thisName);
                                                }
                                                file=new QFile("./"+thisName+"/"+fileName);

                                                QByteArray fileData=QByteArray::fromBase64(body.toUtf8());
                                                if(file->open(QFile::WriteOnly))
                                                {
                                                    file->write(fileData);
                                                    file->close();
                                                }

                                                body=fileName;
                                                delete dir;
                                                delete file;
                                            }
                                        }
                                        else return;
                                    else return;
                                }
                                else return;
                            else {return;}
                            newLog.senderCom=senderCom;
                            newLog.senderName=senderName;
                            newLog.receiverCom=receiverCom;
                            newLog.receiverName=receiverName;
                            newLog.time=time;
                            newLog.body=body;
                            emit coder_receiveMessage(newLog);
                        }
                        default:break;
                    }
        }
        else return;
    }
}
