#ifndef ANALYSISWINDOW_H
#define ANALYSISWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QSet>
#include "Contact.h"

namespace Ui {
class AnalysisWindow;
}

class AnalysisWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AnalysisWindow(QWidget *parent = nullptr);
    ~AnalysisWindow();

    void setAnalysisFiles(const QString &file1, const QString &file2);

private slots:
    void onBackButtonClicked();

private:
    Ui::AnalysisWindow *ui;
    QString filePath1;
    QString filePath2;
    QList<Contact> contacts1;
    QList<Contact> contacts2;

    // 加载数据
    void loadContactsFromFile(const QString &filePath, QList<Contact> &contacts);

    // 分析功能
    void analyzeTagStatistics();      // 标签统计
    void analyzeCommonContacts();     // 共同联系人
    void analyzeSocialRelation();     // 社交关联度

    // 辅助函数
    double calculateCommonContactRatio();      // 计算共同联系人比例
    double calculateCitySimilarity();          // 计算城市相似度
    double calculateTagSimilarity();           // 计算标签相似度
    double calculateSocialRelationScore();     // 计算社交关联度得分
    QString getRelationLevel(double score);    // 获取关系级别

    // 统计函数
    QMap<QString, int> countTags(const QList<Contact> &contacts);
    QMap<QString, int> countCities(const QList<Contact> &contacts);
};

#endif // ANALYSISWINDOW_H
