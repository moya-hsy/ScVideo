#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <QWidget>
#include <QApplication>
#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>
#include <QPropertyAnimation>

namespace Ui {
class countDown;
}

class countDown : public QWidget
{
    Q_OBJECT

public:
    explicit countDown(QWidget *parent = nullptr);
    ~countDown();

private slots:
    void updateCountdown();

private:
    Ui::countDown *ui;
    QLabel *countdownLabel;
    QTimer *timer;
    int countdown;

signals:
    void closeThisWindow();

};

#endif // COUNTDOWN_H
