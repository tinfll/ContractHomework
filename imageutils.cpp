#include "imageutils.h"
#include <QImageReader>
#include <QImageWriter>
#include <QDirIterator>
#include <QThread>
#include <QPainter>

ImageUtils::ImageUtils(QObject *parent) : QObject(parent)
{
}

bool ImageUtils::convertToPng(const QString &sourcePath, const QString &destPath)
{
    QFileInfo sourceInfo(sourcePath);

    // 检查源文件是否存在
    if (!sourceInfo.exists() || !sourceInfo.isFile()) {
        qWarning() << "源文件不存在或不是文件:" << sourcePath;
        return false;
    }

    // 检查是否是支持的格式
    QString format = QImageReader::imageFormat(sourcePath);
    QStringList supported = getSupportedInputFormats();
    if (!supported.contains(format, Qt::CaseInsensitive)) {
        qWarning() << "不支持的图片格式:" << format << "文件:" << sourcePath;
        return false;
    }

    // 确定目标路径
    QString targetPath = destPath;
    if (targetPath.isEmpty()) {
        // 默认：相同目录，改为.png后缀
        targetPath = sourceInfo.path() + "/" +
                     sourceInfo.completeBaseName() + ".png";
    }

    // 如果目标文件已存在且与源文件相同，跳过
    if (QFileInfo(targetPath) == sourceInfo) {
        qDebug() << "源文件和目标文件相同，跳过:" << sourcePath;
        return true;
    }

    // 检查目标文件是否已存在（如果允许覆盖则跳过此检查）
    if (QFile::exists(targetPath) && QFileInfo(targetPath) != sourceInfo) {
        qWarning() << "目标文件已存在:" << targetPath;
        return false;
    }

    // 加载图片
    QImage image;
    if (!image.load(sourcePath)) {
        qWarning() << "无法加载图片:" << sourcePath;
        return false;
    }

    // 转换到RGBA格式以支持透明通道（如果需要）
    QImage::Format targetFormat = QImage::Format_ARGB32;
    if (!image.hasAlphaChannel() &&
        (format.toLower() == "jpg" || format.toLower() == "jpeg")) {
        // JPEG没有Alpha通道，转换为ARGB32并填充白色背景
        QImage rgbaImage(image.size(), targetFormat);
        rgbaImage.fill(Qt::white);

        QPainter painter(&rgbaImage);
        painter.drawImage(0, 0, image);
        painter.end();

        image = rgbaImage;
    } else {
        // 其他格式直接转换
        image = image.convertToFormat(targetFormat);
    }

    // 保存为PNG
    bool success = image.save(targetPath, "PNG");

    if (success) {
        qDebug() << "转换成功:" << sourcePath << "->" << targetPath
                 << "尺寸:" << image.size() << "格式:PNG";

        // 可选：复制文件修改时间
        QFile sourceFile(sourcePath);
        QFile targetFile(targetPath);

        QDateTime lastModified = sourceFile.fileTime(QFileDevice::FileModificationTime);
        targetFile.setFileTime(lastModified, QFileDevice::FileModificationTime);
    } else {
        qWarning() << "转换失败:" << sourcePath << "->" << targetPath;
    }

    return success;
}

int ImageUtils::convertFolderToPng(const QString &folderPath,
                                   bool overwrite,
                                   bool recursive)
{
    QDir dir(folderPath);
    if (!dir.exists()) {
        qWarning() << "文件夹不存在:" << folderPath;
        return 0;
    }

    // 获取所有图片文件
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.jpeg" << "*.bmp" << "*.gif" << "*.tiff" << "*.tif";

    QDirIterator::IteratorFlags flags = recursive ?
                                            QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags;

    QDirIterator it(folderPath, nameFilters, QDir::Files, flags);

    QStringList filesToConvert;
    while (it.hasNext()) {
        QString filePath = it.next();
        if (needsConversion(filePath)) {
            filesToConvert.append(filePath);
        }
    }

    if (filesToConvert.isEmpty()) {
        qDebug() << "没有需要转换的图片文件";
        return 0;
    }

    qDebug() << "找到" << filesToConvert.size() << "个需要转换的文件";

    // 开始转换
    int converted = 0;
    int failed = 0;

    for (int i = 0; i < filesToConvert.size(); ++i) {
        QString sourcePath = filesToConvert[i];
        QFileInfo info(sourcePath);

        // 发出进度信号
        // emit conversionProgress(i + 1, filesToConvert.size(), info.fileName());

        // 确定目标路径
        QString targetPath;
        if (overwrite) {
            // 覆盖模式：直接改为.png后缀
            targetPath = info.path() + "/" + info.completeBaseName() + ".png";

            // 如果目标文件存在且不是源文件，先删除
            if (QFile::exists(targetPath) && targetPath != sourcePath) {
                QFile::remove(targetPath);
            }
        } else {
            // 不覆盖：创建新文件，如果已存在则跳过
            targetPath = info.path() + "/" + info.completeBaseName() + ".png";
            if (QFile::exists(targetPath)) {
                qDebug() << "目标文件已存在，跳过:" << targetPath;
                continue;
            }
        }

        // 执行转换
        bool success = convertToPng(sourcePath, targetPath);

        if (success) {
            converted++;

            // 可选：转换成功后删除原文件（谨慎！）
            // QFile::remove(sourcePath);
        } else {
            failed++;
            qWarning() << "转换失败:" << sourcePath;
        }

        // 让出CPU，避免界面卡死
        QThread::msleep(10);
    }

    qDebug() << "转换完成: 成功" << converted << "个，失败" << failed << "个";
    // emit conversionFinished(converted, failed);

    return converted;
}

bool ImageUtils::needsConversion(const QString &filePath)
{
    QFileInfo info(filePath);
    QString suffix = info.suffix().toLower();

    // 需要转换的格式
    QStringList convertFormats = {"jpg", "jpeg", "bmp", "gif", "tiff", "tif"};

    return convertFormats.contains(suffix);
}

QStringList ImageUtils::getSupportedInputFormats()
{
    // Qt支持的所有可读格式
    QList<QByteArray> formats = QImageReader::supportedImageFormats();
    QStringList result;

    for (const QByteArray &format : formats) {
        result.append(QString(format).toLower());
    }

    return result;
}
