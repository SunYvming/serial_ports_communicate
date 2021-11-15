#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSerialPortInfo>
#include <QSerialPort>
#include <QTimer>
#include <QListWidgetItem>

#include "customwidget.h"
#include "coder.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool openSerialPort(QString portName);

    const QString &getUserName() const;
    void setUserName(const QString &newUserName);
    virtual void closeEvent (QCloseEvent * event);


signals:
    void customBeat(QString com);
    void customChanged(QListWidgetItem *item);
    void customMessageRead(log_t newMessage);
    void customMessageWrite(log_t newMessage);

private:
    Ui::MainWindow *ui;
    QSerialPort *serialCom;
    QTimer *timer;
    QString userName;
    QList<CustomWidget*> customs;
    Coder *coder;
    QByteArray buffer;
    bool flag=false;


private slots:
    void serial_readData();
    void serial_writeData(QString com,QString name,QString time,QString body);
    void timer_timeOut();
    void serial_receiveBeat(QString com,QString name,QString time);
    void customList_itemClicked(QListWidgetItem *item);
    void customMessageSend(QString com,QString name,QString time,QString body);
};

#endif // MAINWINDOW_H
