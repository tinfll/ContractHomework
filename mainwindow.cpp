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
    QString dataDir = exeDir + "/Data/";

    // 列出该目录下所有文件
    QDir dir(dataDir);
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
        QString fullPath = dataDir + selectedFile;

        if(!QFile::exists(fullPath)){
            QMessageBox::warning(this, "错误",
                                 "文件不存在: " + fullPath);
            return;
        }
          qDebug() << "选择的文件:" << fullPath;

        // 创建或显示通讯录窗口
        if (!contactBookWindow) {
            contactBookWindow = new ContactBookWindow(this);
        }

        // 设置文件名
        contactBookWindow->setFilePath(fullPath);

        // 显示通讯录窗口，隐藏主窗口
        contactBookWindow->show();
        this->hide();
    }

}

//两个用户文件进行
void MainWindow::onCompareButtonClicked(){
    qDebug() << "compare";

    QString exeDir = QCoreApplication::applicationDirPath();
    QString dataDir = exeDir + "/Data/";

    QDir dir(dataDir);


    QStringList filters;
    filters << "*.txt";
    QStringList fileList = dir.entryList(filters, QDir::Files);


    // 选择第一个文件
    bool ok1;
    QString selectedFile1 = QInputDialog::getItem(this,
                                                  "选择第一个通讯录文件",
                                                  "请选择第一个要比较的通讯录文件:",
                                                  fileList,
                                                  0,
                                                  false,
                                                  &ok1);

    if (!ok1 || selectedFile1.isEmpty()) {
        return;  // 用户取消选择
    }

    // 从列表中移除已选的文件
    QStringList remainingFiles = fileList;
    remainingFiles.removeAll(selectedFile1);

    if (remainingFiles.isEmpty()) {
        QMessageBox::information(this, "提示", "没有其他文件可供比较！");
        return;
    }

    // 选择第二个文件
    bool ok2;
    QString selectedFile2 = QInputDialog::getItem(this,
                                                  "选择第二个通讯录",
                                                  "请选择第二个要比较的通讯录:",
                                                  remainingFiles,
                                                  0,
                                                  false,
                                                  &ok2);

    if (!ok2 || selectedFile2.isEmpty()) {
        return;  // 用户取消选择
    }

    QString fullPath1 = dataDir + selectedFile1;
    QString fullPath2 = dataDir + selectedFile2;

    // 检查文件是否存在
    if (!QFile::exists(fullPath1) || !QFile::exists(fullPath2)) {
        QMessageBox::warning(this, "错误", "选择的文件不存在！");
        return;
    }

    qDebug() << "选择的文件1:" << fullPath1;
    qDebug() << "选择的文件2:" << fullPath2;

    // 创建或显示分析窗口
    if (!analysisWindow) {
        analysisWindow = new AnalysisWindow(this);
    }

    // 设置要分析的文件
    analysisWindow->setAnalysisFiles(fullPath1, fullPath2);

    // 显示分析窗口，隐藏主窗口
    analysisWindow->show();
    this->hide();

}
