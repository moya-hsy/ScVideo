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

    //rrs
    screen = QGuiApplication::primaryScreen();
    rrs->height = screen->size().height();
    rrs->width = screen->size().width();
    rrs->offset_x = 0;
    rrs->offset_y = 0;

    //路径
    QString path = QStandardPaths::writableLocation(QStandardPaths::MoviesLocation);
    outputPath = forge_outpath(path.toStdString());
}

///参数设置函数
void ScreenRecord::initConfigOfFullScreen(double fps, int quality, int timeLimit, int frame_height, int frame_width)
{
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
    screen = QGuiApplication::primaryScreen();
    rrs->height = screen->size().height();
    rrs->width = screen->size().width();
    rrs->offset_x = 0;
    rrs->offset_y = 0;
}

///获取自定义地址
void ScreenRecord::setOutputPath(QString path)
{
    outputPath = forge_outpath(path.toStdString());
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

///路径信息检查
void ScreenRecord::cleanOutputPath()
{
    QFile checkExistFile(QString::fromStdString(outputPath));
    if(checkExistFile.exists())
    {
        qDebug() << "文件已存在";
        if(checkExistFile.remove())
        {
            qDebug() << "同名文件已删除";
        }else
        {
            qDebug() << "同名文件删除失败";
        }
    }
}

///打印配置信息
void ScreenRecord::printCommand()
{
    qDebug() << "Values rrs: \nw*h: " << rrs->width << " x " << rrs->height << "\noffset: " << rrs->offset_x << ", " << rrs->offset_y << '\n';
    qDebug() << "values vs:"
             << "\nfps: " << vs->fps << "\nquality: " << vs->quality << "\ntime: " << QString::number(vs->recordTime) << "\n";
    qDebug() << "Directory: " << QString::fromStdString(outputPath);
}

///设置命令
QString ScreenRecord::getCommandLine()
{
    printCommand();

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
                  " " + '"' + QString::fromStdString(outputPath) + '"';
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
                  " " + '"' + QString::fromStdString(outputPath) + '"';
    }
    return command;
}

/////开始录制
void ScreenRecord::record()
{
    cleanOutputPath();
    startRecordCommand = getCommandLine();
    qDebug() << "################命令行信息####################";
    qDebug() << startRecordCommand;

    recordProcess = new QProcess();
    recordProcess->setProcessChannelMode(QProcess::MergedChannels);

    recordStream = new QTextStream(recordProcess);

    qDebug() << "->开始录制";

    recordProcess->start(startRecordCommand);

    QObject::connect(recordProcess, &QProcess::readyReadStandardOutput, [&](){
        qDebug() << recordProcess->readAll();
        qInfo()<<u8"time:"<<QDateTime::currentDateTime();
    });
}
