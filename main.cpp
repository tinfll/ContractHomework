#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include <QDebug>
#include <QFile>


int main(int argc, char *argv[]) {
    // 创建应用程序对象
    QApplication app(argc, argv);

    // 创建主窗口
    MainWindow window;

    // 显示窗口
    window.show();

    // 进入事件循环
    return app.exec();
}
