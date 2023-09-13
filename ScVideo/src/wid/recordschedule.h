#ifndef RECORDSCHEDULE_H
#define RECORDSCHEDULE_H

#include <QWidget>
#include <QApplication>
#include <QDesktopWidget>
#include <QProgressBar>
#include <QLabel>
#include <QTimer>
//#include <QAudioRecorder>
#include <QVBoxLayout>
#include <QPushButton>

namespace Ui {
class recordSchedule;
}

class recordSchedule : public QWidget
{
    Q_OBJECT

public:
    explicit recordSchedule(QWidget *parent = nullptr);
    ~recordSchedule();

private:
    Ui::recordSchedule *ui;

private slots:
    void updateProgressBar();
    void togglePauseRecording();
    void finishWindow();

public slots:
    void showThisWindow();


private:
    void setupUi();
    void updateTimeLabel();

    QProgressBar *progressBar;
    QLabel *timeLabel;
    QTimer *timer;
//    QAudioRecorder *audioRecorder;
    int timeElapsed;
    static const int MAX_RECORDING_TIME = 300;
    QPushButton *pauseButton;
    QPushButton *stopButton;
    bool pause;

signals:
    void closeThisWindow();
};

#endif // RECORDSCHEDULE_H
