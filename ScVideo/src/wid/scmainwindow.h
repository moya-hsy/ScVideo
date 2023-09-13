#ifndef SCMAINWINDOW_H
#define SCMAINWINDOW_H

#include <QAction>
#include <QScreen>
#include <QColorDialog>
#include <QCloseEvent>
#include <condition_variable>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <functional>
#include <QMainWindow>
#include <QMessageBox>
#include <QMenu>
#include <mutex>
#include <memory>
#include <QSize>
#include <QShortcut>
#include <QSystemTrayIcon>
#include <QStandardPaths>
#include <QSystemTrayIcon>
#include <QDateTime>
#include <QtWidgets/QComboBox>
#include <string>
//#include <include/libavcodec/adts_parser.h>
#include "countdown.h"
#include "recordschedule.h"
#include "screenrecord.h"


namespace Ui {
class scMainWindow;
}

class scMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit scMainWindow(QWidget *parent = nullptr);
    ~scMainWindow();

private slots:
    void on_pushButtonStart_clicked();
    void showThisWindow();
    void on_watermarkColorPushButton_clicked();
    void on_toolButton_clicked();
    void on_horizontalSlider_sliderMoved(int position);
    void on_radioButton24_clicked();
    void on_radioButton30_clicked();
    void on_radioButton60_clicked();
    void on_action_triggered();
    void changeShortcut(QKeySequence startShortCut, QKeySequence pauseShortCut, QKeySequence stopShortcut);
    void on_pushButtonFullScreen_clicked();
    void on_pushButtonSelectArea_clicked();
    void enable_or_disable_tabs(bool val);

    void on_pushButtonStop_clicked();

private:
    Ui::scMainWindow *ui;

    countDown *countdownWindow;

    recordSchedule *recordScheduleWindow;

    QColor watermarkCurrentColor = Qt::black;

    std::string outFilePath;

    void setQualityANDCompression(int a);

    QScreen *screen;

    std::string forge_outpath(std::string outFilePath);

//    AreaSelector *areaSelector;
    screenRecord *screenRecorder;

    void alignValues();

signals:
    void signal_close();
    void signal_show(bool);
    void signal_recording(bool);

};

#endif // SCMAINWINDOW_H
