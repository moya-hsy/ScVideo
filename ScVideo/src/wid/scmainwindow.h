#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ScMainWindow; }
QT_END_NAMESPACE

class ScMainWindow : public QWidget
{
    Q_OBJECT

public:
    ScMainWindow(QWidget *parent = nullptr);
    ~ScMainWindow();

private:
    Ui::ScMainWindow *ui;
};
