// ImageUtils.h
#ifndef IMAGEUTILS_H
#define IMAGEUTILS_H

#include <QObject>
#include <QImage>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

class ImageUtils : public QObject
{
    Q_OBJECT
public:
    explicit ImageUtils(QObject *parent = nullptr);

    // 转换单个文件
    static bool convertToPng(const QString &sourcePath, const QString &destPath = "");

    // 批量转换文件夹中的图片
    static int convertFolderToPng(const QString &folderPath,
                                  bool overwrite = false,
                                  bool recursive = false);

    // 检查是否需要转换
    static bool needsConversion(const QString &filePath);

    // 获取支持的输入格式
    static QStringList getSupportedInputFormats();

signals:
    void conversionProgress(int current, int total, const QString &filename);
    void conversionFinished(int converted, int failed);
};

#endif // IMAGEUTILS_H
