#include "scmainwindow.h"
#include "ui_scmainwindow.h"
#include "screenrecord.h"
#include "quicksr.h"

VideoSettings vs;
RecordingRegionSettings rrs;

std::string deviceName;

void scMainWindow::alignValues() {
    ///rrs values
//    if (ui->pushButtonFullScreen->isChecked()) {
//        rrs.width = screen->size().width();
//        rrs.height = screen->size().height();
//        rrs.offset_x = 0;
//        rrs.offset_y = 0;
        
//        rrs.screen_number = 0;
//    } else {
//        rrs.height = areaSelector->getHeight();
//        rrs.width = areaSelector->getWidth();
//        rrs.offset_x = areaSelector->getX();
//        rrs.offset_y = areaSelector->getY();
//    }
    
    ///vs values
    vs.fps = 24;
    if (ui->radioButton30->isChecked())
        vs.fps = 30;
    else if (ui->radioButton24->isChecked())
        vs.fps = 24;
    else if (ui->radioButton60->isChecked())
        vs.fps = 60;
    setQualityANDCompression(ui->horizontalSlider->value());
    
    ///rrs values
    rrs.width = screen->size().width();
    rrs.height = screen->size().height();
    rrs.offset_x = 0;
    rrs.offset_y = 0;

    vs.audioOn = false;
//    vs.audioOn = ui->radioButtonYes->isChecked();
    outFilePath = ui->lineEditPath->text().toStdString();
    
//    deviceName = ui->comboBox->currentText().toStdString();
//    minimizeInSysTray = ui->checkBoxMinimize->isChecked();
}

scMainWindow::scMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::scMainWindow)
{
    screen = QGuiApplication::primaryScreen();
    ui->setupUi(this);
    ui->lineEditPath->setReadOnly(true);
    ui->lineEditPath->setText(QString::fromStdString(forge_outpath(QStandardPaths::writableLocation(QStandardPaths::MoviesLocation).toStdString())));
//    areaSelector = new AreaSelector();

}

scMainWindow::~scMainWindow()
{
    delete ui;
}

////录制////
void scMainWindow::on_pushButtonStart_clicked()
{
    if (ui->lineEditPath->text().isEmpty()) {
        QMessageBox::information(this, tr("无效路径"),
                                 tr("包含文件保存路径的消息框不能为空"));
        return;
    }
//    this->hide();
//    countdownWindow = new countDown();
//    countdownWindow->show();
//    recordScheduleWindow = new recordSchedule();
//    connect(countdownWindow, &countDown::closeThisWindow, recordScheduleWindow, &recordSchedule::showThisWindow);
//    connect(recordScheduleWindow, &recordSchedule::closeThisWindow, this, &scMainWindow::showThisWindow);
    ui->pushButtonStart->setDisabled(true);
    ui->pushButtonStop->setEnabled(true);
    ui->pushButtonPause->setEnabled(true);
    enable_or_disable_tabs(false);

    alignValues();

    // 打印信息
    qDebug() << "Values rrs: \n wxh: " << rrs.width << " x " << rrs.height << "\noffset: " << rrs.offset_x << ", " << rrs.offset_y
             << "\n fullscreen: " << ui->pushButtonFullScreen->isChecked() << "\n";
    qDebug() << "values di vs:"
             << "\n fps: " << vs.fps << "\n quality: " << vs.quality << "\n audio: " << QString::number(vs.audioOn) << "\n";
    qDebug() << "Directory: " << QString::fromStdString(outFilePath);
//    qDebug() << "DeviceName: " << QString::fromStdString(deviceName);
//    qDebug() << "minimize:: " << minimizeInSysTray;

    try {
//        screenRecorder = std::make_unique<screenRecord>(rrs, vs, outFilePath, deviceName);
        screenRecorder = new screenRecord(rrs, vs, outFilePath, deviceName);
        qDebug() << "建立screenRecord对象";
        try{
            screenRecorder->runByCmd();
            qDebug() << "录制中";
        }catch(...){

        }
    } catch (...) {
    }
}

void scMainWindow::showThisWindow()
{
    this->show();
}


void scMainWindow::on_watermarkColorPushButton_clicked()
{
    QColor selectedColor = QColorDialog::getColor(watermarkCurrentColor, this, "Select Color");
    if (selectedColor.isValid()) {
        watermarkCurrentColor = selectedColor;
    }
}


void scMainWindow::on_toolButton_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, tr("选择存储路径"), QString(QStandardPaths::writableLocation(QStandardPaths::MoviesLocation)));
    path = path.endsWith(".mp4") ? path : path + ".mp4";
    ui->lineEditPath->setText(path);

    outFilePath = path.toStdString();
    qDebug() << "outFilePath:" << QString::fromStdString(outFilePath);
}


void scMainWindow::on_horizontalSlider_sliderMoved(int position)
{
    setQualityANDCompression(position);
}

void scMainWindow::setQualityANDCompression(int position)
{
    vs.quality = position;
}

void scMainWindow::on_radioButton24_clicked()
{
    vs.fps = 24;
}

void scMainWindow::on_radioButton30_clicked()
{
    vs.fps = 30;
}

void scMainWindow::on_radioButton60_clicked()
{
    vs.fps = 60;
}

void scMainWindow::on_action_triggered()
{
    quickSr *quickWindow = new quickSr();
    quickWindow->show();
    connect(quickWindow, &quickSr::shortcutInfoChanged, this, &scMainWindow::changeShortcut);
}

void scMainWindow::changeShortcut(QKeySequence startShortCut, QKeySequence pauseShortCut, QKeySequence stopShortcut)
{
    ui->pushButtonStart->setShortcut(startShortCut);
    ui->pushButtonStop->setShortcut(stopShortcut);
    ui->pushButtonPause->setShortcut(pauseShortCut);
}


void scMainWindow::on_pushButtonFullScreen_clicked()
{
    ui->pushButtonSelectArea->setChecked(false);
    ui->pushButtonFullScreen->setChecked(true);

    screen = QGuiApplication::primaryScreen();
    rrs.width = screen->size().width();
    rrs.height = screen->size().height();
    rrs.offset_x = 0;
    rrs.offset_y = 0;

    qDebug() << "fullscreen: " << rrs.width << "x" << rrs.height;

    emit signal_show(false);
}

std::string scMainWindow::forge_outpath(std::string outFilePath) {
    std::string ending = ".mp4";
    QDateTime time = QDateTime::currentDateTime();
    QString timeString = time.toString("yyyy-MM-dd_HH-mm-ss");
    std::string timeStdStriong = timeString.toStdString();
    if (!std::equal(ending.rbegin(), ending.rend(), outFilePath.rbegin())) {
        ending = "/";
        if (std::equal(ending.rbegin(), ending.rend(), outFilePath.rbegin()))
        {
            std::string s1 = timeStdStriong + ".mp4";
            outFilePath += s1;
        }
        else {
            std::string s1 = "/" + timeStdStriong + ".mp4";
            outFilePath += s1;
        }
    }
    return outFilePath;
}

void scMainWindow::on_pushButtonSelectArea_clicked()
{
    static bool first_call = true;
    bool state = ui->pushButtonSelectArea->isChecked();
    qDebug() << state;

    qDebug() << "rrs.fullscreen = false";
    ui->pushButtonSelectArea->setChecked(true);
    ui->pushButtonFullScreen->setChecked(false);
    // 防止再次点击
    qDebug()<<"111";
    if(first_call)
    {
        first_call = false;
//        areaSelector->slot_init();
    }
    emit signal_show(true);
}

void scMainWindow::enable_or_disable_tabs(bool val) {
    QList<QWidget *> list = ui->tab_1->findChildren<QWidget *>();
    QList<QWidget *> list2 = ui->tab_2->findChildren<QWidget *>();
    list.append(list2);
    foreach (QWidget *w, list) { w->setEnabled(val); }
}




void scMainWindow::on_pushButtonStop_clicked()
{
    screenRecorder->stopByCmd();
}

