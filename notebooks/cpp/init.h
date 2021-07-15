
#pragma cling add_include_path("/usr/include/x86_64-linux-gnu/qt5/QtCore")
#pragma cling add_include_path("/usr/include/x86_64-linux-gnu/qt5")
#pragma cling load("Qt5Core")
#define __PIC__

#ifndef __qversiontagging_wrapper__
#define __qversiontagging_wrapper__

#define QT_NO_VERSION_TAGGING
 
#include <QtCore/qversiontagging.h>
 
#endif

#include <QtGlobal>
#include <QString>
#include <QDebug>
#include <iostream>

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        std::cout << localMsg.constData() << std::endl;
        break;
    case QtInfoMsg:
        std::cout << localMsg.constData() << std::endl;
        break;
    case QtWarningMsg:
        fprintf(stderr, "%s\n", localMsg.constData());
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
   }
}

void cppInit() {   
    qInstallMessageHandler(myMessageOutput);
    
    qDebug() << "C++ Backend Initialized!";
}

