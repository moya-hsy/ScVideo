#include "recordschedule.h"
#include "ui_recordschedule.h"

recordSchedule::recordSchedule(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::recordSchedule)
{
    ui->setupUi(this);
    recordSchedule::setupUi();
    pause = false;
    resize(minimumWidth(), minimumHeight());
    //    audioRecorder->record();
}

void recordSchedule::updateProgressBar()
{
    timeElapsed++;
    //    progressBar->setValue(timeElapsed);
    updateTimeLabel();
}

void recordSchedule::setupUi()
{
    // 获取屏幕的宽度和高度
    int screenWidth = QApplication::desktop()->width();
    // 设置窗口大小和位置
    int windowWidth = 400;
    int windowHeight = 1000;
    int x = (screenWidth - windowWidth) / 2;
    int y = 0;
    this->setGeometry(x, y, windowWidth, windowHeight);
    // 窗口位置，样式调整
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);


    //    setWindowTitle("录制进度");

    // 进度条
    //    progressBar = new QProgressBar;
    //    progressBar->setRange(0, MAX_RECORDING_TIME);

    // 设置倒计时面板
    timeLabel = new QLabel("00:00");



    // 两个按钮
    stopButton = new QPushButton("停止录制");
    pauseButton = new QPushButton("暂停录制");

    // 按钮槽函数
    connect(stopButton, &QPushButton::clicked, this, &recordSchedule::finishWindow);
    connect(pauseButton, &QPushButton::clicked, this, &recordSchedule::togglePauseRecording);
    //    QHBoxLayout *buttonLayout = new QHBoxLayout;

    // 水平布局
    QHBoxLayout *timeLayout = new QHBoxLayout;
    timeLayout->addWidget(new QLabel("录制时长: "));
    timeLayout->addWidget(timeLabel);
    timeLayout->addWidget(pauseButton);
    timeLayout->addWidget(stopButton);

    // 计时器
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &recordSchedule::updateProgressBar);

    //    audioRecorder = new QAudioRecorder;
    //    audioRecorder->setOutputLocation(QUrl::fromLocalFile("output.wav"));

    // 窗口布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    //    mainLayout->addWidget(progressBar);
    mainLayout->addLayout(timeLayout);

    timeElapsed = 0;
}

void recordSchedule::updateTimeLabel()
{
    int minutes = timeElapsed / 60;
    int seconds = timeElapsed % 60;
    timeLabel->setText(QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0')));
}

void recordSchedule::togglePauseRecording()
{
    if (pause)
    {
        //        audioRecorder->record();
        timer->start(1000);
        pause = false;
        pauseButton->setText("暂停录制");
    }
    else
    {
        //        audioRecorder->pause();
        timer->stop();
        pause = true;
        pauseButton->setText("继续录制");
    }
}

void recordSchedule::finishWindow()
{
    close();
    emit closeThisWindow();
}

void recordSchedule::showThisWindow()
{
    show();
    timer->start(1000);
}

recordSchedule::~recordSchedule()
{
    delete ui;
}
