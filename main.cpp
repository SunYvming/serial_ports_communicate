#include "config.h"
#include "debugthread.h"
#include "joindialog.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    //QFont font = a.font();
    //font.setPointSize(10);
    //a.setFont(font);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "serial_ports_communicate_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
#if DEBUG_MULTI==1
    joinDialog w;
    w.show();
#else
    DebugThread* threads[DEBUG_MULTI];
    for(int i=0;i<DEBUG_MULTI;i++)
    {
        threads[i]=new DebugThread();
    }
    for(int i=0;i<DEBUG_MULTI;i++)
    {
        threads[i]->start();
    }
#endif
    return a.exec();
}
