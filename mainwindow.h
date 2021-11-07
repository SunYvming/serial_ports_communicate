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

private:
    Ui::MainWindow *ui;
    QSerialPort *serialCom;
    QTimer *timer;

private slots:
    void serial_readData();
    void serial_writeData(const QByteArray &data);
    void timer_timeOut();
};

#endif // MAINWINDOW_H
