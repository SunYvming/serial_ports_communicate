#include "coder.h"

#include <QVariant>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonValue>

#include <QMetaEnum>

#include <QTime>

Coder *coder=nullptr;

Coder::Coder()
{

}

QByteArray Coder::encoder(Kind kind,QString senderCom,QString senderName,QString receiver,QString body)
{
    switch (kind)
    {
        case Kind::Beat:
        {
            QJsonObject senderObject;
            senderObject.insert("Com",senderCom);
            senderObject.insert("Name",senderName);

            QJsonObject bodyObject;
            bodyObject.insert("Time",QDateTime::currentDateTime().toString("hh:mm:ss:zzz"));
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
            return nullptr;

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
    }
    return nullptr;
}

void Coder::decoder(QByteArray input)
{
    QString com;
    QString name;
    QString time;

    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(input,&jsonError);
    if(!document.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        if(document.isObject())
        {
            QJsonObject object = document.object();
            if(object.contains("Kind"))
            {
                if(object.value("Kind").isString())
                {
                    switch (Kind(QMetaEnum::fromType<Coder::Kind>().keysToValue(object.value("Kind").toString().toLatin1())))
                    {
                        case Kind::Beat:
                        {
                            if(object.contains("Sender"))
                            {
                                if(object.value("Sender").isObject())
                                {
                                    QJsonObject senderObject=object.value("Sender").toObject();
                                    if(senderObject.contains("Com")&&senderObject.contains("Name"))
                                    {
                                        if(senderObject.value("Com").isString()&&senderObject.value("Name").isString())
                                        {
                                            com=senderObject.value("Com").toString();
                                            name=senderObject.value("Name").toString();
                                        }
                                        else return;
                                    }
                                    else return;
                                }
                                else return;

                            }
                            else return;
                            if(object.contains("Body"))
                            {
                                if(object.value("Body").isObject())
                                {
                                    QJsonObject bodyObject=object.value("Body").toObject();
                                    if(bodyObject.contains("Time"))
                                    {
                                        if(bodyObject.value("Time").isString())
                                            time=bodyObject.value("Time").toString();
                                        else return;
                                    }
                                    else return;
                                }
                                else return;
                            }
                            else {return;}
                            emit coder_receiveBeat(com,name,time);
                        }
                        case Kind::Debug:
                        {
                            //啥都不干
                        }
                        default:break;
                    }
                }
                else return;
            }
        }
    }
}
