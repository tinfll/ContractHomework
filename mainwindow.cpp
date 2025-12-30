#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "analysiswindow.h"
#include <QFontDatabase>
#include <QInputDialog>
#include <QMessageBox>
#include <QDir>
#include <QDebug>
#include <QCoreApplication>
#include <QApplication>
#include "contactbookwindow.h"
#include "imageutils.h"
#include <QPainter>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , contactBookWindow(nullptr)
    , analysisWindow(nullptr)
{
    ui->setupUi(this);

    setWindowTitle("日月轮管理系统");
    qDebug() << "MainWindow 构造函数被调用";

    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;

    //都关掉
    if (contactBookWindow) {
        delete contactBookWindow;
    }
    if (analysisWindow) {
        delete analysisWindow;
    }
}

void MainWindow::setupConnections()
{
    //按钮们
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::onExitButtonClicked);
    connect(ui->selectPersonButton, &QPushButton::clicked, this, &MainWindow::onSelectPersonButtonClicked);
    connect(ui->compareButton, &QPushButton::clicked, this, &MainWindow::onCompareButtonClicked);

}

//退出
void MainWindow::onExitButtonClicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "退出", "退出确定?", QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes){
        QApplication::quit();
    }
}

//选择单个用户文件进行操作界面入口+data文件路径传递
void MainWindow::onSelectPersonButtonClicked()
{
    qDebug() << "选择用户按钮被点击！";
    QString exeDir = QCoreApplication::applicationDirPath();
    QString picturesDir = exeDir + "/Data/";

    // 列出该目录下所有文件
    QDir dir(picturesDir);
    /*if (dir.exists()) {
        qDebug() << "目录内容:";
        for (const QString& file : dir.entryList(QDir::Files)) {
            qDebug() << "  - " << file;
        }
    }
    else {
        qDebug() << "目录不存在！";
    }
    qDebug() << "==================";
    */

    QStringList filters;
    filters << "*.txt";
    QStringList fileList = dir.entryList(filters, QDir::Files);
    

    bool ok;
    //标记此处去查轮子可写文件交互逻辑!!!!!!写报告用
    //文件判断空选
    QString selectedFile = QInputDialog::getItem(this, "选择文件", "请选择用户文件", fileList, 0 , false, &ok);

    if(ok && !selectedFile.isEmpty()){
        QString fullPath = picturesDir + selectedFile;

        if(!QFile::exists(fullPath)){
            QMessageBox::warning(this, "错误",
                                 "文件不存在: " + fullPath);
            return;
        }
          qDebug() << "选择的文件:" << fullPath;

        // 创建或显示礼物窗口
        if (!contactBookWindow) {
            contactBookWindow = new ContactBookWindow(this);
        }

        // 设置文件名
        contactBookWindow->setFilePath(fullPath);

        // 显示礼物窗口，隐藏主窗口
        contactBookWindow->show();
        this->hide();
    }

}


void MainWindow::onCompareButtonClicked(){
    qDebug() << "image";

    QString exeDir = QCoreApplication::applicationDirPath();
    QString picturesDir = exeDir + "/picturesDir/";

    QDir dir(picturesDir);

	//调用imageutils列出png文件


    int needConvertCount = 0;
    QStringList allImageFiles = dir.entryList(QDir::Files);
    for (const QString& filename : allImageFiles) {
        if (ImageUtils::needsConversion(picturesDir + filename)) {
            needConvertCount++;
        }
    }


    if (needConvertCount > 0) {
        int reply = QMessageBox::question(this, "发现非PNG图片",
            QString("在Pictures文件夹中发现 %1 个非PNG图片文件。\n\n"
                "为了获得最佳处理效果（支持透明通道特效），\n"
                "是否将它们转换为PNG格式？\n\n"
                "转换后可以解锁完整的Alpha通道处理功能。")
            .arg(needConvertCount),
            QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 执行批量转换
        int converted = ImageUtils::convertFolderToPng(picturesDir, false, false);

        if (converted > 0) {
            QMessageBox::information(this, "转换完成",
                QString("已成功转换 %1 个文件为PNG格式。\n\n"
                    "现在你可以享受完整的Alpha通道处理功能了！")
                .arg(converted));
        }
    }
}

    QStringList filters;

    filters << "*.png";
    QStringList fileList = dir.entryList(filters, QDir::Files);

    if (fileList.isEmpty()) {
        QMessageBox::information(this, "图片库为空",
            "生日图片库是空的！\n\n"
            "你可以：\n"
            "1. 将图片复制到程序目录的Pictures文件夹\n"
            "2. 或者使用示例图片");

        // 添加一个示例图片
        createSampleImage(picturesDir);

        // 重新获取文件列表
        fileList = dir.entryList(filters, QDir::Files);
    }


    bool ok;
    QString selectedFile = QInputDialog::getItem(this,
                                                  "选择第一个礼物文件",
                                                  "请选择第一个要分析的礼物文件:",
                                                  fileList,
                                                  0,
                                                  false,
                                                  &ok);

    if (!ok || selectedFile.isEmpty()) {
        return;  // 用户取消选择
    }

    // 从列表中移除已选的文件
    QStringList remainingFiles = fileList;
    remainingFiles.removeAll(selectedFile);


    if (remainingFiles.isEmpty()) {
        QMessageBox::information(this, "提示", "没有其他文件可供分析！");
        return;
    }


    QString fullPath = picturesDir + selectedFile;
    
    // 检查文件是否存在
    if (!QFile::exists(fullPath)) {
        QMessageBox::warning(this, "错误", "选择的文件不存在！");
        return;
    }

    qDebug() << "选择的文件:" << fullPath;

    // 创建或显示png图片窗口。
    if (!analysisWindow) {
        analysisWindow = new AnalysisWindow(this);
    }

    analysisWindow->loadAndDisplayImage(fullPath);
    // 显示分析窗口，隐藏主窗口
    analysisWindow->show();
    this->hide();

}





void MainWindow::createSampleImage(const QString& picturesDir)
{
    // 创建一个带Alpha通道的示例PNG图片
    QImage sampleImage(400, 300, QImage::Format_ARGB32);
    sampleImage.fill(Qt::transparent);  // 透明背景

    QPainter painter(&sampleImage);
    painter.setRenderHint(QPainter::Antialiasing);

    // 画一个半透明的红色圆
    painter.setBrush(QColor(255, 0, 0, 180));  // 半透明红色
    painter.setPen(QPen(Qt::red, 2));
    painter.drawEllipse(100, 50, 80, 80);

    // 画一个带Alpha渐变的矩形
    QLinearGradient gradient(50, 150, 350, 150);
    gradient.setColorAt(0, QColor(0, 255, 0, 255));     // 不透明绿色
    gradient.setColorAt(1, QColor(0, 255, 0, 50));      // 半透明绿色
    painter.setBrush(gradient);
    painter.setPen(QPen(Qt::green, 2));
    painter.drawRect(50, 150, 300, 80);

    // 添加文字
    painter.setFont(QFont("Arial", 24, QFont::Bold));
    painter.setPen(Qt::blue);
    painter.drawText(80, 250, "Happy Birthday!");

    // 添加Alpha通道提示
    painter.setFont(QFont("Arial", 10));
    painter.setPen(Qt::darkGray);
    painter.drawText(10, 290, "示例图片 - 支持Alpha通道");

    // 保存为PNG
    QString filePath = picturesDir + "sample_birthday.png";
    if (sampleImage.save(filePath, "PNG", 100)) {
        qDebug() << "已创建示例图片:" << filePath;
    }
}
