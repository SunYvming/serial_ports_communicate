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

private:
    Ui::MainWindow *ui;
    QSerialPort *serialCom;
    QTimer *timer;
    QString userName;
    QList<CustomWidget*> customs;
    Coder *coder;


private slots:
    void serial_readData();
    void timer_timeOut();
    void serial_receiveBeat(QString com,QString name,QString time);
    void customList_itemClicked(QListWidgetItem *item);
};

#endif // MAINWINDOW_H
