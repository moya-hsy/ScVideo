#pragma once

#include <QWidget>
#include <QScreen>
#include <QStandardPaths>
#include "fun/screenrecord.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ScMainWindow; }
QT_END_NAMESPACE

class ScMainWindow : public QWidget
{
    Q_OBJECT

public:
    ScMainWindow(QWidget *parent = nullptr);
    ~ScMainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::ScMainWindow *ui;

    ScreenRecord *s1 = NULL;
    ScreenRecord *s2 = NULL;
    ScreenRecord *s3 = NULL;
    ScreenRecord *s4 = NULL;
    ScreenRecord *s5 = NULL;

};
