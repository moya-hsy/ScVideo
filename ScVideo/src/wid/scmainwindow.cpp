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

