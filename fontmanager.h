#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <QString>
#include <QFont>
#include <QApplication>

class FontManager
{
public:
    // 单例模式
    static FontManager& instance();

    // 加载字体
    bool loadFont();

    // 获取字体
    QFont getFont(int pointSize = 20, QFont::Weight weight = QFont::Normal);

    // 应用字体到整个应用程序
    void applyToApplication();

    // 应用字体到特定控件
    void applyToWidget(QWidget* widget);

    // 获取字体家族名
    QString getFontFamily() const { return fontFamily; }

private:
    FontManager();
    ~FontManager() = default;
    FontManager(const FontManager&) = delete;
    FontManager& operator=(const FontManager&) = delete;

    QString fontFamily;
    bool fontLoaded = false;

    // 多种加载方式
    bool loadFromResource();
    bool loadFromFileSystem();
    bool loadFromAbsolutePath();
};

#endif // FONTMANAGER_H
