#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSerialPortInfo>
#include <QSerialPort>
#include <QTimer>

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

private:
    Ui::MainWindow *ui;
    QSerialPort *serialCom;
    QTimer *timer;
    QString userName;

private slots:
    void serial_readData();
    void timer_timeOut();
    void serial_receiveBeat(QString com,QString name,QString time);
};

#endif // MAINWINDOW_H
