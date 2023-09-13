#include <QApplication>
#include "wid/scmainwindow.h"
#include "wid/screenrecord.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMessageBox errorDialog;
    try {
        scMainWindow sc;
        sc.show();
        return a.exec();
    } catch (const std::exception& e) {
        QString message = e.what();
        message += "\n重启程序";
        errorDialog.critical(0, "错误", message);
    }
}
