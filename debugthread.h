#ifndef DEBUGTHREAD_H
#define DEBUGTHREAD_H

#include <QThread>
#include "joindialog.h"

class DebugThread : public QThread
{
    Q_OBJECT
public:
    explicit DebugThread(QObject *parent = nullptr);
    void run()
    {
    }

public slots:
    void slotStop()
    {
        delete w;
        this->quit();
    }

private:
    joinDialog *w;

};

#endif // DEBUGTHREAD_H
