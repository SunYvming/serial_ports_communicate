#include "debugthread.h"

DebugThread::DebugThread(QObject *parent) : QThread(parent)
{
    w=new joinDialog();
    connect(w,&joinDialog::destroyed,this,&DebugThread::slotStop);
    w->show();
}
