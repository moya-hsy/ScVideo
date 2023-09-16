#include "scmainwindow.h"
#include "./ui_scmainwindow.h"

ScMainWindow::ScMainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ScMainWindow)
{
    ui->setupUi(this);
}

ScMainWindow::~ScMainWindow()
{
    delete ui;
}



void ScMainWindow::on_pushButton_2_clicked()
{
    s1 = new ScreenRecord();
    s1->setOutputPath("C:/Project/11.mp4");
    s1->initConfigOfFullScreen(true, 1, 40);
    s1->setWatermarkPath("C:/KKtong/watermark.png");
    s1->record();
}


void ScMainWindow::on_pushButton_clicked()
{
    s1->stopRecord();
}


void ScMainWindow::on_pushButton_3_clicked()
{
    s2 = new ScreenRecord();
    s2->setOutputPath("C:/Project/22.mp4");
    s2->initConfigOfFullScreen(false, 1, 40);
    s2->setWatermarkPath("C:/KKtong/watermark.png");
    s2->record();
}


void ScMainWindow::on_pushButton_8_clicked()
{
    s3 = new ScreenRecord();
    s3->setOutputPath("C:/Project/33.mp4");
    s3->initConfigOfFullScreen(true, 1, 1);
    s3->setWatermarkPath("C:/KKtong/watermark.png");
    s3->record();
}


void ScMainWindow::on_pushButton_9_clicked()
{
    s4 = new ScreenRecord();
    s4->setOutputPath("C:/Project/44.mp4");
    s4->initConfigOfFullScreen(false, 1, 1);
    s4->setWatermarkPath("C:/KKtong/watermark.png");
    s4->record();
}


void ScMainWindow::on_pushButton_10_clicked()
{
    s5 = new ScreenRecord();
    s5->setOutputPath("C:/Project/55.mp4");
    s5->initConfigOfFullScreen(true, 30, 1);
    s5->setWatermarkPath("C:/KKtong/watermark.png");
    s5->record();
}


void ScMainWindow::on_pushButton_7_clicked()
{
    if(s2){
        s2->stopRecord();
    }
}




void ScMainWindow::on_pushButton_4_clicked()
{
    s3->stopRecord();

}


void ScMainWindow::on_pushButton_5_clicked()
{
    s4->stopRecord();

}


void ScMainWindow::on_pushButton_6_clicked()
{
    s5->stopRecord();

}

