#ifndef JOINDIALOG_H
#define JOINDIALOG_H

#include <QDialog>
#include <QList>
#include <QSerialPortInfo>
#include "mycombobox.h"

#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class joinDialog; }
QT_END_NAMESPACE

class joinDialog : public QDialog
{
    Q_OBJECT

public:
    joinDialog(QWidget *parent = nullptr);
    ~joinDialog();
    void openSerialPort();

private:
    Ui::joinDialog *ui;
    QList<QSerialPortInfo> avilablePort;
    MainWindow *mainwindow;

private slots:
    void comboBox_clicked();
    void pushButton_clicked();
};
#endif // JOINDIALOG_H
