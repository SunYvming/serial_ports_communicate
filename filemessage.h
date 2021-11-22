#ifndef FILEMESSAGE_H
#define FILEMESSAGE_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>

namespace Ui {
class FileMessage;
}

class FileMessage : public QWidget
{
    Q_OBJECT

public:
    explicit FileMessage(QWidget *parent = nullptr);
    ~FileMessage();

    void setPairItem(QListWidgetItem *newPairItem);

    void setFileName(const QString &newFileName);

    void setTotal(int newTotal);

    void setIsSender(bool newIsSender);

    void setParentWidget(QListWidget *newParentWidget);

public slots:
    void progressUpdate(QString fileName,int number,int total);

private:
    Ui::FileMessage *ui;
    QListWidgetItem *pairItem;
    QListWidget *parentWidget;
    QString fileName;
    bool isSender;
    int total;

};

#endif // FILEMESSAGE_H
