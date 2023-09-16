#ifndef SCREENRECORD_H
#define SCREENRECORD_H

#include <QObject>
#include <QScreen>
#include <QProcess>
#include <QTextStream>
#include <QGuiApplication>
#include <QStandardPaths>
#include <QTime>
#include <QDebug>
#include <QFile>
#include <QFileInfo>

typedef struct
{
    int width;
    int height;
    int offset_x;
    int offset_y;
} RecordingRegionSetting;

typedef struct
{
    double fps;         // 可为小数，不可为负数
    int quality;        // [1, 50]: 1为无损，50为模糊，25为适中
    int recordTime;     // 录制时长，默认六小时
    int frame_width;    // 滤镜缩放后的宽
    int frame_height;   // 滤镜缩放后的高
    bool scaleByFilter; // 是否通过滤镜缩放
    bool addWatermark;  // 是否添加水印
} VideoSetting;

class ScreenRecord : public QObject
{
    Q_OBJECT
public:
    explicit ScreenRecord(QObject *parent = nullptr);

public:
    /**
     * @brief initConfigOfFullScreen        自定义参数
     * @param addWatermark                  是否添加水印
     * @param fps                           帧数：默认为1，支持小数
     * @param quality                       质量：默认40
     * @param timeLimit                     时长：默认6小时
     * @param frame_height                  缩放后高
     * @param frame_width                   缩放后宽
     * 默认视频缩放为880*500，如保持原分辨率只需frame_height传入-1
     */
    void initConfigOfFullScreen(bool addWatermark, double fps = 1, int quality = 40, int timeLimit = 21600, int frame_height = 500, int frame_width = 880);

    /**
     * @brief setOutputPath                 设置录制视频路径
     * @param path                          传入自定义路径
     * 传入示例
     * C:/Project/name.mp4
     * C:/Project/
     */
    void setOutputPath(QString path);

    void setWatermarkPath(QString path);

    void stopRecord();

public slots:
    /**
     * @brief record    通过命令行启动录制
     */
    void record();

    void startAddWatermark(int intExit);

    void getOutputFile(int intExit);

private:
    RecordingRegionSetting *rrs = NULL;
    VideoSetting *vs = NULL;
    std::string recordOutputPath;
    std::string watermarkPath;
    std::string watermarkFileOutputPath;
    QProcess *recordProcess = NULL;
    QTextStream *recordStream = NULL;
    QProcess *addWatermarkProcess = NULL;
    QTextStream *addWatermarkStream = NULL;

private:
    /**
     * @brief defaultConfig
     * 配置默认信息，默认地址为电脑Video地址，文件名为日期_时间
     */
    void defaultConfig();

    /**
     * @brief forge_outpath
     * @param outputPath
     * @return 修正后的视频地址
     */
    std::string forge_outpath(std::string outputPath);

    /**
     * @brief getCommandLine
     * @return 录屏指令
     */
    QString getRecordCommandLine();

    /**
     * @brief printCommand      打印录屏信息
     */
    void printVideoConfig();

    /**
     * @brief cleanOutputPath   删除已存在的文件
     */
    bool cleanOutputPath(std::string path);

    QString getWatermarkCommandLine();

    bool deleteAndRename(std::string deleteFilePath, std::string renameFilePath);

    std::string addMarkedToFileName(std::string path);
signals:
//    void recordFinished();

};

#endif // SCREENRECORD_H
