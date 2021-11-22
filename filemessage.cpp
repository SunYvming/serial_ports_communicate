#include "filemessage.h"
#include "ui_filemessage.h"

#include <QFile>
#include <QFileInfo>
#include <QFileIconProvider>
#include <QIcon>
#include <QDesktopServices>
#include <QUrl>

FileMessage::FileMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileMessage)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->progressBar->setValue(0);
    ui->progressBar->setTextVisible(false);
}

FileMessage::~FileMessage()
{
    delete ui;
}

void FileMessage::setPairItem(QListWidgetItem *newPairItem)
{
    pairItem = newPairItem;
}

void FileMessage::progressUpdate(QString fileName, int number, int total)
{
    if(this->fileName==fileName)
    {
        if(number==total)
        {
            ui->stackedWidget->setCurrentIndex(1);
            if(isSender)
            {
                ui->openDirButton->hide();
                ui->openFileButton->hide();
            }
            else
            {
                ui->openDirButton->show();
                ui->openFileButton->show();
            }
        }
        else
        {
            ui->progressBar->setValue(number);
        }
        parentWidget->setItemWidget(pairItem,this);
    }
}

void FileMessage::fileReceiveFinish(QString fileName, QString dir)
{
    if(fileName==this->fileName)
    {
        connect(ui->openFileButton,&QPushButton::clicked,this,[dir]{
            QDesktopServices::openUrl(QUrl::fromLocalFile(dir));
        });
    }

}

const QString &FileMessage::getFileName() const
{
    return fileName;
}

void FileMessage::setParentWidget(QListWidget *newParentWidget)
{
    parentWidget = newParentWidget;
}

void FileMessage::setIsSender(bool newIsSender)
{
    isSender = newIsSender;
}

void FileMessage::setTotal(int newTotal)
{
    total = newTotal;
    ui->progressBar->setRange(0,total);
}

void FileMessage::setFileName(const QString &newFileName)
{
    fileName = newFileName;
    QFileInfo file_info(fileName);
    QFileIconProvider icon_provider;
    QIcon icon = icon_provider.icon(file_info);

    ui->label->setPixmap(icon.pixmap(QSize(50,50)).scaled(50,50));
    ui->fileNameLabel->setText(fileName);
    ui->fileNameLabel_2->setText(fileName);
}
