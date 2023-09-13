#ifndef QUICKSR_H
#define QUICKSR_H

#include <QWidget>
#include <QLineEdit>
#include <QKeyEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

namespace Ui {
class quickSr;
}

class quickSr : public QWidget
{
    Q_OBJECT

private:
    QKeySequence startShortCut;
    QKeySequence pauseShortCut;
    QKeySequence stopShortCut;

public:
    explicit quickSr(QWidget *parent = nullptr);
    ~quickSr();

signals:
    void shortcutInfoChanged(QKeySequence startShortCut, QKeySequence pauseShortCut, QKeySequence stopShortcut);

private:
    Ui::quickSr *ui;

    QString startstr;

private slots:
    void setStartShortcut(QString shortcut);
    void setPauseShortcut(QString shortcut);
    void setStopShortcut(QString shortcut);

};










class ShortcutLineEdit : public QLineEdit
{
    Q_OBJECT

private:
    QString shortcut;

public:
    explicit ShortcutLineEdit(QWidget *parent = nullptr);

signals:
    void shortcutCaptured(const QString &shortcut);

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // QUICKSR_H
