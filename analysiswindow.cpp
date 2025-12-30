#include "analysiswindow.h"
#include "ui_analysiswindow.h"
#include <QFileInfo>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFileDialog>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QRadioButton>      
#include <QDialog>           
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>


AnalysisWindow::AnalysisWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AnalysisWindow)
{
    ui->setupUi(this);

    // 连接按钮信号
    connect(ui->applyEffectButton, &QPushButton::clicked,
            this, &AnalysisWindow::onApplyEffectButtonClicked);
    connect(ui->saveImageButton, &QPushButton::clicked,
            this, &AnalysisWindow::onSaveImageButtonClicked);
    connect(ui->backButton, &QPushButton::clicked,
            this, &AnalysisWindow::onBackButtonClicked);

    // 设置窗口标志
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
}

AnalysisWindow::~AnalysisWindow()
{
    delete ui;
}

void AnalysisWindow::loadAndDisplayImage(const QString &imagePath)
{
    currentImagePath = imagePath;

    // 加载图片
    if (!originalImage.load(imagePath)) {
        QMessageBox::warning(this, "错误",
                             QString("无法加载图片：\n%1\n\n请检查文件格式和权限。")
                                 .arg(imagePath));
        return;
    }

    // 确保图片是ARGB32格式（支持Alpha通道）
    if (originalImage.format() != QImage::Format_ARGB32 &&
        originalImage.format() != QImage::Format_ARGB32_Premultiplied) {
        originalImage = originalImage.convertToFormat(QImage::Format_ARGB32);
    }

    // 初始化processedImage
    processedImage = originalImage;

    // 更新显示
    updateImageDisplay();

    // 提取并显示Alpha通道
    extractAlphaChannel();

    // 更新图片信息
    updateImageInfo();

    qDebug() << "图片加载成功:" << imagePath
             << "尺寸:" << originalImage.size()
             << "格式: ARGB32"
             << "有Alpha通道:" << originalImage.hasAlphaChannel();
}

void AnalysisWindow::updateImageDisplay()
{
    if (processedImage.isNull()) {
        ui->originalImageLabel->setText("<图片加载失败>");
        return;
    }

    // 缩放图片以适应标签，保持纵横比
    QPixmap pixmap = QPixmap::fromImage(processedImage);


    QSize labelSize = ui->originalImageLabel->size();
    QPixmap scaledPixmap = pixmap.scaled(labelSize,
                                         Qt::KeepAspectRatio,
                                         Qt::SmoothTransformation);

    ui->originalImageLabel->setPixmap(scaledPixmap);
    ui->originalImageLabel->setAlignment(Qt::AlignCenter);
}


void AnalysisWindow::extractAlphaChannel()
{
    if (originalImage.isNull()) return;

    // 创建灰度图像来显示Alpha通道
    alphaChannelImage = QImage(originalImage.size(), QImage::Format_Grayscale8);

    for (int y = 0; y < originalImage.height(); ++y) {
        const QRgb *srcLine = reinterpret_cast<const QRgb*>(originalImage.scanLine(y));
        uchar *dstLine = alphaChannelImage.scanLine(y);

        for (int x = 0; x < originalImage.width(); ++x) {
            // 提取Alpha值（0-255）作为灰度值
            dstLine[x] = qAlpha(srcLine[x]);
        }
    }

    // 显示Alpha通道
    QPixmap alphaPixmap = QPixmap::fromImage(alphaChannelImage);
    QSize labelSize = ui->alphaChannelLabel->size();
    QPixmap scaledAlphaPixmap = alphaPixmap.scaled(labelSize,
                                                   Qt::KeepAspectRatio,
                                                   Qt::SmoothTransformation);

    ui->alphaChannelLabel->setPixmap(scaledAlphaPixmap);
    ui->alphaChannelLabel->setAlignment(Qt::AlignCenter);

    // 添加Alpha通道说明
    QString alphaInfo = analyzeAlphaChannel();
    ui->alphaChannelLabel->setToolTip(alphaInfo);
}


void AnalysisWindow::updateImageInfo()
{
    if (originalImage.isNull()) return;

    QFileInfo fileInfo(currentImagePath);

    QString infoText = QString(
                           "📁 文件信息:\n"
                           "  文件名: %1\n"
                           "  路径: %2\n"
                           "  大小: %3 KB\n\n"
                           "🖼️ 图片信息:\n"
                           "  尺寸: %4 × %5 像素\n"
                           "  格式: PNG (ARGB32)\n"
                           "  颜色深度: 32位\n"
                           "  Alpha通道: %6\n\n"
                           "🔍 Alpha分析:\n%7")
                           .arg(fileInfo.fileName())
                           .arg(fileInfo.path())
                           .arg(fileInfo.size() / 1024.0, 0, 'f', 1)
                           .arg(originalImage.width())
                           .arg(originalImage.height())
                           .arg(originalImage.hasAlphaChannel() ? "✅ 支持" : "❌ 不支持")
                           .arg(analyzeAlphaChannel());

    ui->imageInfoLabel->setText(infoText);
}

QString AnalysisWindow::analyzeAlphaChannel() const
{
    if (originalImage.isNull() || !originalImage.hasAlphaChannel()) {
        return "  此图片没有Alpha通道（透明通道）。";
    }

    int transparentPixels = 0;
    int semiTransparentPixels = 0;
    int opaquePixels = 0;
    int totalPixels = originalImage.width() * originalImage.height();

    for (int y = 0; y < originalImage.height(); ++y) {
        const QRgb *scanLine = reinterpret_cast<const QRgb*>(originalImage.scanLine(y));
        for (int x = 0; x < originalImage.width(); ++x) {
            int alpha = qAlpha(scanLine[x]);

            if (alpha == 0) {
                transparentPixels++;      // 完全透明
            } else if (alpha < 255) {
                semiTransparentPixels++;  // 半透明
            } else {
                opaquePixels++;           // 完全不透明
            }
        }
    }

    double transparentPercent = (transparentPixels * 100.0) / totalPixels;
    double semiPercent = (semiTransparentPixels * 100.0) / totalPixels;
    double opaquePercent = (opaquePixels * 100.0) / totalPixels;

    return QString(
               "  🔹 完全透明: %1 像素 (%2%)\n"
               "  🔸 半透明: %3 像素 (%4%)\n"
               "  🔹 不透明: %5 像素 (%6%)\n"
               "  📊 总像素: %7")
        .arg(transparentPixels)
        .arg(transparentPercent, 0, 'f', 1)
        .arg(semiTransparentPixels)
        .arg(semiPercent, 0, 'f', 1)
        .arg(opaquePixels)
        .arg(opaquePercent, 0, 'f', 1)
        .arg(totalPixels);
}

void AnalysisWindow::onApplyEffectButtonClicked()
{
    if (originalImage.isNull()) {
        QMessageBox::warning(this, "错误", "请先加载图片！");
        return;
    }

    // 弹出效果选择对话框
    QDialog effectDialog(this);
    effectDialog.setWindowTitle("选择艺术特效");
    effectDialog.setFixedSize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(&effectDialog);

    QLabel *titleLabel = new QLabel("🎨 选择要应用的艺术特效");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; margin: 10px;");
    layout->addWidget(titleLabel);

    // 效果选项
    QRadioButton *bayerButton = new QRadioButton("Bayer抖动（复古印刷效果）");
    QRadioButton *pixelButton = new QRadioButton("像素化马赛克");
    QRadioButton *alphaEdgeButton = new QRadioButton("Alpha边缘发光");
    QRadioButton *colorSeparationButton = new QRadioButton("色彩分离");

    bayerButton->setChecked(true);

    layout->addWidget(bayerButton);
    layout->addWidget(pixelButton);
    layout->addWidget(alphaEdgeButton);
    layout->addWidget(colorSeparationButton);

    layout->addSpacing(20);

    QPushButton *applyBtn = new QPushButton("✨ 应用特效");
    QPushButton *cancelBtn = new QPushButton("取消");

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(applyBtn);
    btnLayout->addWidget(cancelBtn);
    layout->addLayout(btnLayout);

    // 连接按钮
    connect(applyBtn, &QPushButton::clicked, [&](){
        if (bayerButton->isChecked()) {
            processedImage = applyBayerDithering(originalImage);
        } else if (pixelButton->isChecked()) {
            processedImage = applyPixelation(originalImage, 10);
        } else if (alphaEdgeButton->isChecked()) {
            // 这里可以添加Alpha边缘发光效果
            QMessageBox::information(this, "即将推出", "Alpha边缘发光效果正在开发中...");
            return;
        } else if (colorSeparationButton->isChecked()) {
            // 这里可以添加色彩分离效果
            QMessageBox::information(this, "即将推出", "色彩分离效果正在开发中...");
            return;
        }

        updateImageDisplay();
        effectDialog.accept();

        QMessageBox::information(this, "成功", "特效已应用！\n点击'保存图片'可以保存处理后的效果。");
    });

    connect(cancelBtn, &QPushButton::clicked, [&](){
        effectDialog.reject();
    });

    effectDialog.exec();
}

void AnalysisWindow::onSaveImageButtonClicked()
{
    if (processedImage.isNull()) {
        QMessageBox::warning(this, "错误", "没有可保存的图片！");
        return;
    }

    QString defaultPath = QCoreApplication::applicationDirPath() +
                          "/Outputs/birthday_processed_" +
                          QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") +
                          ".png";

    QString savePath = QFileDialog::getSaveFileName(this,
                                                    "保存处理后的图片",
                                                    defaultPath,
                                                    "PNG图片 (*.png);;JPEG图片 (*.jpg);;所有文件 (*.*)");

    if (savePath.isEmpty()) return;

    bool success = processedImage.save(savePath);

    if (success) {
        QMessageBox::information(this, "成功",
                                 QString("图片已保存到:\n%1\n\n"
                                         "尺寸: %2×%3\n"
                                         "格式: PNG")
                                     .arg(savePath)
                                     .arg(processedImage.width())
                                     .arg(processedImage.height()));
    } else {
        QMessageBox::warning(this, "错误", "保存失败！");
    }
}

void AnalysisWindow::onBackButtonClicked()
{
    emit windowClosed();
    this->close();
}

void AnalysisWindow::closeEvent(QCloseEvent *event)
{
    emit windowClosed();
    QMainWindow::closeEvent(event);
}


// ============ 图像处理函数实现 ============

QImage AnalysisWindow::applyBayerDithering(const QImage &input)
{
    QImage output = input.convertToFormat(QImage::Format_ARGB32);

    // 4x4 Bayer矩阵
    int bayerMatrix[4][4] = {
        { 0, 8, 2, 10 },
        { 12, 4, 14, 6 },
        { 3, 11, 1, 9 },
        { 15, 7, 13, 5 }
    };

    for (int y = 0; y < output.height(); ++y) {
        QRgb *scanLine = reinterpret_cast<QRgb*>(output.scanLine(y));
        for (int x = 0; x < output.width(); ++x) {
            QRgb pixel = scanLine[x];
            int alpha = qAlpha(pixel);

            // 如果完全透明，跳过处理
            if (alpha == 0) {
                continue;
            }

            // 计算灰度值（考虑Alpha）
            QColor color(pixel);
            int gray = (color.red() * 0.299 +
                        color.green() * 0.587 +
                        color.blue() * 0.114);

            int threshold = bayerMatrix[y % 4][x % 4] * 16;  // 0-240

            // 二值化，但保留Alpha
            QRgb newPixel;
            if (gray > threshold) {
                newPixel = qRgba(255, 255, 255, alpha);  // 白色
            } else {
                newPixel = qRgba(0, 0, 0, alpha);        // 黑色
            }

            scanLine[x] = newPixel;
        }
    }

    return output;
}

QImage AnalysisWindow::applyPixelation(const QImage &input, int blockSize)
{
    QImage output = input.convertToFormat(QImage::Format_ARGB32);

    for (int y = 0; y < output.height(); y += blockSize) {
        for (int x = 0; x < output.width(); x += blockSize) {
            // 计算区块的平均颜色和平均Alpha
            int r = 0, g = 0, b = 0, a = 0;
            int count = 0;

            for (int dy = 0; dy < blockSize && y + dy < output.height(); dy++) {
                QRgb *line = reinterpret_cast<QRgb*>(output.scanLine(y + dy));
                for (int dx = 0; dx < blockSize && x + dx < output.width(); dx++) {
                    QRgb pixel = line[x + dx];
                    r += qRed(pixel);
                    g += qGreen(pixel);
                    b += qBlue(pixel);
                    a += qAlpha(pixel);
                    count++;
                }
            }

            if (count > 0) {
                QRgb avgPixel = qRgba(r / count, g / count, b / count, a / count);

                // 填充整个区块
                for (int dy = 0; dy < blockSize && y + dy < output.height(); dy++) {
                    QRgb *line = reinterpret_cast<QRgb*>(output.scanLine(y + dy));
                    for (int dx = 0; dx < blockSize && x + dx < output.width(); dx++) {
                        line[x + dx] = avgPixel;
                    }
                }
            }
        }
    }

    return output;
}
