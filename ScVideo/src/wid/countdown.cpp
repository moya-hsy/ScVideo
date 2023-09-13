#include "countdown.h"
#include "ui_countdown.h"

countDown::countDown(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::countDown)
{
    ui->setupUi(this);
    // 不绘制窗口的边框和标题栏，置于所有窗口上
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    // 透明背景
    setAttribute(Qt::WA_TranslucentBackground);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    countdownLabel = new QLabel(this);
    countdownLabel->setFont(QFont("Arial", 48));
    layout->addWidget(countdownLabel);

    setLayout(layout);

    countdown = 3;
    countdownLabel->setText(QString::number(countdown));

    timer = new QTimer(this);
    timer->start(1000);
    // 超时触发
    connect(timer, &QTimer::timeout, this, &countDown::updateCountdown);

}

void countDown::updateCountdown()
{
    countdown--;
    if (countdown >= 0) {
        countdownLabel->setText(QString::number(countdown));
    } else {
        timer->stop();
        close();
        emit closeThisWindow();
    }
}



countDown::~countDown()
{
    delete ui;
}
