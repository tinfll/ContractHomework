#include "FontManager.h"
#include <QFontDatabase>
#include <QFile>
#include <QDebug>
#include <QCoreApplication>
#include <QWidget>
#include <QApplication>

FontManager::FontManager()
    : fontFamily("Microsoft YaHei")  // 默认字体
    , fontLoaded(false)
{
}

FontManager& FontManager::instance()
{
    static FontManager instance;
    return instance;
}

bool FontManager::loadFont()
{
    // 如果已经加载过，直接返回
    if (fontLoaded) {
        return true;
    }

    qDebug() << "开始加载像素字体...";

    // 尝试多种加载方式
    if (loadFromResource()) {
        fontLoaded = true;
        return true;
    }

    if (loadFromFileSystem()) {
        fontLoaded = true;
        return true;
    }

    if (loadFromAbsolutePath()) {
        fontLoaded = true;
        return true;
    }

    qWarning() << "所有字体加载方式都失败了，使用默认字体";
    return false;
}

QFont FontManager::getFont(int pointSize, QFont::Weight weight)
{
    QFont font(fontFamily, pointSize);
    font.setWeight(weight);
    return font;
}

void FontManager::applyToApplication()
{
    QFont appFont = getFont();
    QApplication::setFont(appFont);
    qDebug() << "已将字体应用到整个应用程序:" << fontFamily;
}

void FontManager::applyToWidget(QWidget* widget)
{
    if (!widget) return;

    QFont widgetFont = getFont();
    widget->setFont(widgetFont);

    // 递归应用到所有子控件
    for (QObject* child : widget->children()) {
        if (QWidget* childWidget = qobject_cast<QWidget*>(child)) {
            childWidget->setFont(widgetFont);
            applyToWidget(childWidget);
        }
    }
}

bool FontManager::loadFromResource()
{
    QString resourcePath = ":/fonts/fusion-pixel-10px-monospaced-zh_hant.ttf";
    qDebug() << "尝试从资源文件加载:" << resourcePath;

    int fontId = QFontDatabase::addApplicationFont(resourcePath);
    if (fontId == -1) {
        qDebug() << "从资源文件加载失败";
        return false;
    }

    QStringList families = QFontDatabase::applicationFontFamilies(fontId);
    if (families.isEmpty()) {
        qDebug() << "资源文件中没有找到字体家族";
        return false;
    }

    fontFamily = families.first();
    qDebug() << "从资源文件加载成功，字体家族:" << fontFamily;
    return true;
}

bool FontManager::loadFromFileSystem()
{
    // 尝试多种可能的相对路径
    QStringList possiblePaths = {
        "fonts/fusion-pixel-10px-monospaced-zh_hant.ttf",
        "../fonts/fusion-pixel-10px-monospaced-zh_hant.ttf",
        "./fonts/fusion-pixel-10px-monospaced-zh_hant.ttf",
        "fusion-pixel-10px-monospaced-zh_hant.ttf"
    };

    for (const QString &relativePath : possiblePaths) {
        QString fullPath = QCoreApplication::applicationDirPath() + "/" + relativePath;
        qDebug() << "尝试从文件系统加载:" << fullPath;

        if (QFile::exists(fullPath)) {
            int fontId = QFontDatabase::addApplicationFont(fullPath);
            if (fontId != -1) {
                QStringList families = QFontDatabase::applicationFontFamilies(fontId);
                if (!families.isEmpty()) {
                    fontFamily = families.first();
                    qDebug() << "从文件系统加载成功，字体家族:" << fontFamily;
                    return true;
                }
            }
        }
    }

    return false;
}

bool FontManager::loadFromAbsolutePath()
{
    QString absolutePath = "C:/Users/tinf/Documents/ContactSystem/fonts/fusion-pixel-10px-monospaced-zh_hant.ttf";
    qDebug() << "尝试从绝对路径加载:" << absolutePath;

    if (QFile::exists(absolutePath)) {
        int fontId = QFontDatabase::addApplicationFont(absolutePath);
        if (fontId != -1) {
            QStringList families = QFontDatabase::applicationFontFamilies(fontId);
            if (!families.isEmpty()) {
                fontFamily = families.first();
                qDebug() << "从绝对路径加载成功，字体家族:" << fontFamily;
                return true;
            }
        }
    }

    qDebug() << "绝对路径加载失败";
    return false;
}
