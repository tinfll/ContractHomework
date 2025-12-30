#ifndef ANALYSISWINDOW_H
#define ANALYSISWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QString>

namespace Ui {
class AnalysisWindow;
}

class AnalysisWindow : public QMainWindow
{
    Q_OBJECT

public:
    // 删除原来的setAnalysisFiles，改用新的函数
    explicit AnalysisWindow(QWidget *parent = nullptr);
    ~AnalysisWindow();

    // 新函数：加载并显示图片
    void loadAndDisplayImage(const QString &imagePath);

signals:
    // 新增信号：窗口关闭时通知主窗口
    void windowClosed();

protected:
    // 重写关闭事件
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onApplyEffectButtonClicked();    // 应用特效
    void onSaveImageButtonClicked();      // 保存图片
    void onBackButtonClicked();           // 返回主界面

private:
    Ui::AnalysisWindow *ui;

    // 图片相关
    QImage originalImage;          // 原始图片
    QImage processedImage;         // 处理后的图片
    QImage alphaChannelImage;      // Alpha通道图像
    QString currentImagePath;      // 当前图片路径

    // 图片分析函数
    void updateImageDisplay();                    // 更新图片显示
    void extractAlphaChannel();                   // 提取Alpha通道
    void updateImageInfo();                       // 更新图片信息
    QString analyzeAlphaChannel() const;          // 分析Alpha通道

    // 图像处理函数
    QImage applyBayerDithering(const QImage &input);  // Bayer抖动
    QImage applyPixelation(const QImage &input, int blockSize); // 像素化
};

#endif // ANALYSISWINDOW_H
