#include <QApplication>
#include "fun/screenrecord.h"
#include <QTimer>
#include <Qthread>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
//#include "wid/scmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    ScMainWindow w;
//    w.show();
    //test-1
//    ScreenRecord s;
//    s.initConfigOfFullScreen(24, 25, 15);
//    s.setOutputPath("C:/QT Project");
//    s.record();
//    QTimer timer;
//    timer.setSingleShot(true);
//    timer.start(10000);
//    QObject::connect(&timer, &QTimer::timeout, [&](){
//        s.stopByCmd();
//    });

    //test-2
//    QThread t_a;
//    ScreenRecord s1;
//    s1.moveToThread(&t_a);
//    s1.setOutputPath("C:/Project/11.mp4");
//    s1.initConfigOfFullScreen(24, 25, 10);
//    QProcess::connect(&t_a, &QThread::started, &s1, &ScreenRecord::record);

//    QThread t_b;
//    ScreenRecord s2;
//    s2.moveToThread(&t_b);
//    s2.setOutputPath("C:/Project/22.mp4");
//    s2.initConfigOfFullScreen(24, 25, 10);
//    QProcess::connect(&t_b, &QThread::started, &s2, &ScreenRecord::record);
//    t_a.start();
//    t_b.start();
//    t_a.wait();
//    t_b.wait();

    const int numThreads = 5;
    QList<QThread*> threadList;
    QList<ScreenRecord*> recordList;
    qInfo()<<u8"===================== start =========================";

    for (int i = 0; i < numThreads; ++i)
    {
        QThread* thread = new QThread();
        ScreenRecord* record = new ScreenRecord();

        record->moveToThread(thread);
        switch (i) {
        case 0:
            record->setOutputPath("C:/Project/11.mp4");
            record->initConfigOfFullScreen(1, 40, 10, 1080);
            break;
        case 1:
            record->setOutputPath("C:/Project/.mp4");
            record->initConfigOfFullScreen(1, 41, 10, 720);
            break;
        case 2:
            record->setOutputPath("C:/Project/158");
            record->initConfigOfFullScreen(1, 40, 10, 500);
            break;
        case 3:
            record->setOutputPath("C:/Project/");
            record->initConfigOfFullScreen(1, 43, 10, 360);
            break;
        case 4:
            record->setOutputPath("C:/QT Project/158");
            record->initConfigOfFullScreen(1, 44, 10, 240);
            break;
        default:
            break;
        }

        QObject::connect(thread, &QThread::started, record, &ScreenRecord::record);

        threadList.append(thread);
        recordList.append(record);
        qInfo()<<u8"===================== case: "<<i;
    }

    for (int i = 0; i < numThreads; ++i)
    {
        threadList[i]->start();
        qInfo()<<u8"===================== start thread: "<<i;
    }

    for (int i = 0; i < numThreads; ++i)
    {
        threadList[i]->wait();
        //qInfo()<<u8"===================== start thread: "<<i;
    }



    qInfo()<<u8"===================== end =========================";
    return 0;
    //return a.exec();
}
