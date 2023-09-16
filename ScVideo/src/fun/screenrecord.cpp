#include "screenrecord.h"

ScreenRecord::ScreenRecord(QObject *parent)
    : QObject{parent}
{
    //new ptr
    vs = new VideoSetting();
    rrs = new RecordingRegionSetting();

    defaultConfig();
}

///默认参数设置
void ScreenRecord::defaultConfig()
{
    //vs
    vs->recordTime = 21600;
    vs->scaleByFilter = true;
    vs->fps = 1;
    vs->quality = 40;
    vs->frame_width = 500;
    vs->frame_height = 880;
    vs->addWatermark = false;

    //rrs
    QScreen *screen = QGuiApplication::primaryScreen();
    rrs->height = screen->size().height();
    rrs->width = screen->size().width();
    rrs->offset_x = 0;
    rrs->offset_y = 0;

    //路径
    QString path = QStandardPaths::writableLocation(QStandardPaths::MoviesLocation);
    recordOutputPath = forge_outpath(path.toStdString());
    watermarkFileOutputPath = "";
    watermarkPath = "";
}

///参数设置函数
void ScreenRecord::initConfigOfFullScreen(bool addWaterMark, double fps, int quality, int timeLimit, int frame_height, int frame_width)
{
    if(addWaterMark == true)
    {
        vs->addWatermark = true;
    }else{
        vs->addWatermark = false;
    }
    if(fps <= 0)
    {
        vs->fps = 6;
    }else{
        vs->fps = fps;
    }
    if(quality <= 0 || quality > 50)
    {
        vs->quality = 35;
    }else{
        vs->quality = quality;
    }
    if(timeLimit <= 0 || timeLimit > 21600)
    {
        vs->recordTime = 21600;
    }else{
        vs->recordTime = timeLimit;
    }
    if(frame_height <= 0)
    {
        vs->scaleByFilter = false;
    }else
    {
        vs->scaleByFilter = true;
        if(frame_width <= 0)
        {
            vs->frame_height = frame_height / 2 * 2;
            vs->frame_width = vs->frame_height / 9 * 16;
        }else{
            vs->frame_height = frame_height;
            vs->frame_width = frame_width;
        }
    }
    QScreen *screen = QGuiApplication::primaryScreen();
    rrs->height = screen->size().height();
    rrs->width = screen->size().width();
    rrs->offset_x = 0;
    rrs->offset_y = 0;
}

///获取自定义地址
void ScreenRecord::setOutputPath(QString path)
{
    recordOutputPath = forge_outpath(path.toStdString());
}

///获取水印图片地址
void ScreenRecord::setWatermarkPath(QString path)
{
    if(path != "")
    {
        QFile checkValid(path);
        if(checkValid.exists())
        {
            watermarkPath = path.toStdString();
        }else{
            QTextStream errorStream(stderr);
            errorStream << "文件无效: " << path << endl;
        }
    }else{
        vs->addWatermark = false;
    }
}

///录制地址修正
std::string ScreenRecord::forge_outpath(std::string outFilePath) {
    std::string ending = ".mp4";
    QDateTime time = QDateTime::currentDateTime();
    QString timeString = time.toString("yyyy-MM-dd_HH-mm-ss");
    std::string timeStdString = timeString.toStdString();
    if (!std::equal(ending.rbegin(), ending.rend(), outFilePath.rbegin())) {
        ending = "/";
        if (std::equal(ending.rbegin(), ending.rend(), outFilePath.rbegin()))
        {
            std::string s1 = timeStdString + ".mp4";
            outFilePath += s1;
        }
        else {
            std::string s1 = "/" + timeStdString + ".mp4";
            outFilePath += s1;
        }
    }
    return outFilePath;
}

///获取暂时输出文件名字
std::string ScreenRecord::addMarkedToFileName(std::string path)
{
    QFileInfo fileInfo(QString::fromStdString(path));

    int lastDotPos = QString::fromStdString(path).lastIndexOf('.');
    if(lastDotPos != -1 && lastDotPos < QString::fromStdString(path).length() - 1)
    {
        QString leftSuffix = QString::fromStdString(path).left(lastDotPos);

        QString suffix = fileInfo.suffix();

        QString markedFileName = leftSuffix + "-marked." + suffix;

        return markedFileName.toStdString();
    }

    qDebug() << "转换失败";

    return "";
}

///删除同名文件
bool ScreenRecord::cleanOutputPath(std::string path)
{
    QFile checkExistFile(QString::fromStdString(path));
    if(checkExistFile.exists())
    {
        qDebug() << "文件已存在";
        if(checkExistFile.remove())
        {
            qDebug() << "同名文件已删除";
            return true;
        }else{
            qDebug() << "同名文件删除失败";
            return false;
        }
    }
    return true;
}

///水印文件修改名字
bool ScreenRecord::deleteAndRename(std::string deleteFilePath, std::string renameFilePath)
{
    QFile deleteFile(QString::fromStdString(deleteFilePath));
    QFile renameFile(QString::fromStdString(renameFilePath));

    if(deleteFile.exists() && renameFile.exists())
    {
        QString name = deleteFile.fileName();
        if(cleanOutputPath(deleteFilePath))
        {
            if(renameFile.rename(name))
            {
                return true;
            }else{
                return false;
            }
        }else{
            qDebug() << "原文件无法删除";
        }
    }
    return false;
}

///打印配置信息
void ScreenRecord::printVideoConfig()
{
    qDebug() << "Values rrs: \nw*h: " << rrs->width << " x " << rrs->height << "\noffset: " << rrs->offset_x << ", " << rrs->offset_y << '\n';
    qDebug() << "values vs:"
             << "\nfps: " << vs->fps << "\nquality: " << vs->quality << "\ntime: " << QString::number(vs->recordTime) << "\n";
    qDebug() << "录屏文件地址: " << QString::fromStdString(recordOutputPath);
    qDebug() << "水印文件地址: " << QString::fromStdString(watermarkPath);
    qDebug() << "加水印录屏文件地址: " << QString::fromStdString(watermarkFileOutputPath);
}

///设置录屏命令
QString ScreenRecord::getRecordCommandLine()
{
    printVideoConfig();

    QString command;
    if(vs->scaleByFilter == true)
    {
        command = "ffmpeg -f gdigrab -framerate " + QString::number(vs->fps) +
                  " -offset_x " + QString::number(rrs->offset_x) + " -offset_y " + QString::number(rrs->offset_y) +
                  " -video_size " + QString::number(rrs->width) + "x" + QString::number(rrs->height) +
                  " -i desktop -crf " + QString::number(vs->quality) +
                  " -vf scale=" + QString::number(vs->frame_width) + ":" + QString::number(vs->frame_height) +
                  " -c:v libx264" +
                  " -t " + QString::number(vs->recordTime) +
                  " -pix_fmt yuv420p"
                  " " + '"' + QString::fromStdString(recordOutputPath) + '"';
    }
    else
    {
        command = "ffmpeg -f gdigrab -framerate " + QString::number(vs->fps) +
                  " -offset_x " + QString::number(rrs->offset_x) +
                  " -offset_y " + QString::number(rrs->offset_y) +
                  " -video_size " + QString::number(rrs->width) + "x" + QString::number(rrs->height) +
                  " -i desktop -qp " + QString::number(vs->quality) +
                  " -c:v libx264" +
                  " -pix_fmt yuv420p"
                  " " + '"' + QString::fromStdString(recordOutputPath) + '"';
    }
    return command;
}

///设置水印命令
QString ScreenRecord::getWatermarkCommandLine()
{
    watermarkFileOutputPath = addMarkedToFileName(recordOutputPath);

    QString command = "ffmpeg -i \"" + QString::fromStdString(recordOutputPath) + '"' +
                      " -i " + '"' + QString::fromStdString(watermarkPath) + '"' +
                      " -filter_complex overlay=10:10 -c:v libx264 " +
                      '"' + QString::fromStdString(watermarkFileOutputPath) + '"';

    return command;
}

///开始录制
void ScreenRecord::record()
{
    if(cleanOutputPath(recordOutputPath))
    {
        QString startRecordCommand = getRecordCommandLine();
        qDebug() << "################录屏命令行信息####################";
        qDebug() << startRecordCommand;

        recordProcess = new QProcess();
        recordProcess->setProcessChannelMode(QProcess::MergedChannels);

        recordStream = new QTextStream(recordProcess);

        qDebug() << "->->->->->->->->->->->->->->->->->->->->->->->->开始录制";

        recordProcess->start(startRecordCommand);

        QObject::connect(recordProcess, &QProcess::readyReadStandardOutput, [&](){
            qDebug() << recordProcess->readAll();
            qInfo()<<u8"time:"<<QDateTime::currentDateTime();
        });
        if(vs->addWatermark == true && watermarkPath != "")
        {
            qDebug() << QString::fromStdString(watermarkFileOutputPath);
            qDebug() << "条件成立-----------------------------------";
            QObject::connect(recordProcess, SIGNAL(finished(int)), this, SLOT(startAddWatermark(int)));
        }
    }else{
        qDebug() << "录制失败：输出文件有误";
    }
}

///开始添加水印
void ScreenRecord::startAddWatermark(int intExit)
{
    qDebug() << "触发";
    addWatermarkProcess = new QProcess();
    addWatermarkProcess->setProcessChannelMode(QProcess::MergedChannels);

    QString addWatermarkCommandLine = getWatermarkCommandLine();
    qDebug() << "#################加水印命令行信息#######################";
    qDebug() << addWatermarkCommandLine;

    qDebug() << "->->->->->->->->->->->->->->->->->->->->->->->->加水印";
    addWatermarkProcess->start(addWatermarkCommandLine);

    recordStream = new QTextStream(addWatermarkProcess);

    QObject::connect(addWatermarkProcess, &QProcess::readyReadStandardOutput, [&](){
        qDebug() << addWatermarkProcess->readAll();
        qInfo()<<u8"time:"<<QDateTime::currentDateTime();
    });

    QObject::connect(addWatermarkProcess, SIGNAL(finished(int)), this, SLOT(getOutputFile(int)));
}

///获得输出文件
void ScreenRecord::getOutputFile(int intExit)
{
    deleteAndRename(recordOutputPath, watermarkFileOutputPath);
    qDebug() << "->->->->->->->->->->->->->->->->->->->->->->->->成功生成文件";
}

///停止录制
void ScreenRecord::stopRecord()
{
    if (recordProcess->isOpen())
    {
        recordProcess->write("q");
    }
}
