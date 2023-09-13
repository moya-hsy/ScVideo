#include "quicksr.h"
#include "ui_quicksr.h"

quickSr::quickSr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::quickSr)
{
    ui->setupUi(this);
    setWindowTitle("快捷键设置窗口");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 快捷键设置
    ShortcutLineEdit *startShortcutLineEdit = new ShortcutLineEdit(this);
    startShortcutLineEdit->setFixedWidth(200);
    startShortcutLineEdit->setText("");
    ShortcutLineEdit *pauseShortcutLineEdit = new ShortcutLineEdit(this);
    pauseShortcutLineEdit->setFixedWidth(200);
    ShortcutLineEdit *stopShortcutLineEdit = new ShortcutLineEdit(this);
    stopShortcutLineEdit->setFixedWidth(200);

    QPushButton *clearButtonOfSa = new QPushButton("清除", this);
    QPushButton *clearButtonOfPa = new QPushButton("清除", this);
    QPushButton *clearButtonOfSo = new QPushButton("清除", this);
    QPushButton *saveButton = new QPushButton("确定", this);
    QPushButton *cancleButton = new QPushButton("取消", this);


    QLabel *startLable = new QLabel("开始录制: ", this);
    QLabel *pauseLable = new QLabel("开始录制: ", this);
    QLabel *stopLable = new QLabel("开始录制: ", this);

    // 四个水平布局
    QHBoxLayout *inputLayoutOfSa = new QHBoxLayout;
    QHBoxLayout *inputLayoutOfPa = new QHBoxLayout;
    QHBoxLayout *inputLayoutOfSo = new QHBoxLayout;
    QHBoxLayout *layoutOfButton = new QHBoxLayout;

    inputLayoutOfSa->addWidget(startLable);
    inputLayoutOfSa->addWidget(startShortcutLineEdit);
    inputLayoutOfSa->addWidget(clearButtonOfSa);

    inputLayoutOfPa->addWidget(pauseLable);
    inputLayoutOfPa->addWidget(pauseShortcutLineEdit);
    inputLayoutOfPa->addWidget(clearButtonOfPa);

    inputLayoutOfSo->addWidget(stopLable);
    inputLayoutOfSo->addWidget(stopShortcutLineEdit);
    inputLayoutOfSo->addWidget(clearButtonOfSo);

    layoutOfButton->addWidget(cancleButton);
    layoutOfButton->addWidget(saveButton);

    mainLayout->addLayout(inputLayoutOfSa);
    mainLayout->addLayout(inputLayoutOfPa);
    mainLayout->addLayout(inputLayoutOfSo);
    mainLayout->addLayout(layoutOfButton);

    // 三个清除按钮
    connect(clearButtonOfSa, &QPushButton::clicked, startShortcutLineEdit, &ShortcutLineEdit::clear);
    connect(clearButtonOfPa, &QPushButton::clicked, pauseShortcutLineEdit, &ShortcutLineEdit::clear);
    connect(clearButtonOfSo, &QPushButton::clicked, stopShortcutLineEdit, &ShortcutLineEdit::clear);

    // 将输入的快捷键从字符转到QKeySequence，并保存在窗口类中
    connect(startShortcutLineEdit, &ShortcutLineEdit::shortcutCaptured, this, &quickSr::setStartShortcut);
    connect(pauseShortcutLineEdit, &ShortcutLineEdit::shortcutCaptured, this, &quickSr::setPauseShortcut);
    connect(stopShortcutLineEdit, &ShortcutLineEdit::shortcutCaptured, this, &quickSr::setStopShortcut);

    // 设定点击确定按钮完成快捷键的更改
    connect(saveButton, &QPushButton::clicked, [this]() {
        emit shortcutInfoChanged(startShortCut, pauseShortCut, stopShortCut);
        close();
    });

}

void quickSr::setStartShortcut(QString shortcut)
{
    startShortCut = QKeySequence::fromString(shortcut);
}

void quickSr::setPauseShortcut(QString shortcut)
{
    pauseShortCut = QKeySequence::fromString(shortcut);
}

void quickSr::setStopShortcut(QString shortcut)
{
    stopShortCut = QKeySequence::fromString(shortcut);
}

quickSr::~quickSr()
{
    delete ui;
}







ShortcutLineEdit::ShortcutLineEdit(QWidget *parent) : QLineEdit(parent)
{
    setReadOnly(true);
}

void ShortcutLineEdit::keyPressEvent(QKeyEvent *event)
{
    shortcut = QKeySequence(event->key() | event->modifiers()).toString(QKeySequence::NativeText);
    setText(shortcut);
    emit shortcutCaptured(shortcut);
}
