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

    Q_PROPERTY(QRect geometry READ getGeometry WRITE setGeometry NOTIFY geometryChange)

    QRect getGeometry()
    {
        return this->geometry();
    }

signals:
    void geometryChange();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::joinDialog *ui;
    QList<QSerialPortInfo> avilablePort;
    MainWindow *mainwindow;
    bool        m_bDrag;
    QPoint      mouseStartPoint;
    QPoint      windowTopLeftPoint;

private slots:
    void comboBox_clicked();
    void pushButton_clicked();
    void setGeometry(const QRect &rect)
    {
        this->QWidget::setGeometry(rect);
        emit geometryChange();
    }
    void pushButton_2_clicked();
};
#endif // JOINDIALOG_H
