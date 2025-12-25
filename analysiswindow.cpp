#include "analysiswindow.h"
#include "ui_analysiswindow.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <cmath>

AnalysisWindow::AnalysisWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AnalysisWindow)
{
    ui->setupUi(this);

    // 连接返回按钮
    connect(ui->backButton, &QPushButton::clicked, this, &AnalysisWindow::onBackButtonClicked);
}

AnalysisWindow::~AnalysisWindow()
{
    delete ui;
}

//加载文件
void AnalysisWindow::setAnalysisFiles(const QString &file1, const QString &file2)
{
    filePath1 = file1;
    filePath2 = file2;

    // 从文件名提取显示名
    QFileInfo info1(file1);
    QFileInfo info2(file2);

    QString title = QString("通讯录分析 - %1 vs %2")
                        .arg(info1.fileName())
                        .arg(info2.fileName());
    setWindowTitle(title);

    // 更新UI显示文件名
    ui->file1NameLabel->setText(info1.fileName());
    ui->file2NameLabel->setText(info2.fileName());

    // 加载联系人数据
    loadContactsFromFile(file1, contacts1);
    loadContactsFromFile(file2, contacts2);

    // 执行分析
    analyzeTagStatistics();
    analyzeCommonContacts();
    analyzeSocialRelation();
}

//加载文件
void AnalysisWindow::loadContactsFromFile(const QString &filePath, QList<Contact> &contacts)
{
    contacts.clear();

    if (!QFile::exists(filePath)) {
        QMessageBox::warning(this, "错误", "文件不存在: " + filePath);
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法打开文件: " + filePath);
        return;
    }

    QTextStream in(&file);
    int lineCount = 0;
    int successCount = 0;

    while (!in.atEnd()) {
        lineCount++;
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        Contact contact;
        if (contact.parseFromString(line)) {
            contacts.append(contact);
            successCount++;
        }
    }

    file.close();

    qDebug() << "从" << filePath << "加载了" << successCount << "个联系人(共" << lineCount << "行)";
}

// 统计标签
QMap<QString, int> AnalysisWindow::countTags(const QList<Contact> &contacts)
{
    QMap<QString, int> tagCount;

    for (const Contact &contact : contacts) {
        for (const QString &tag : contact.tags) {
            if (!tag.isEmpty()) {
                tagCount[tag]++;
            }
        }
    }

    return tagCount;
}

// 统计城市
QMap<QString, int> AnalysisWindow::countCities(const QList<Contact> &contacts)
{
    QMap<QString, int> cityCount;

    for (const Contact &contact : contacts) {
        if (!contact.city.isEmpty()) {
            cityCount[contact.city]++;
        }
    }

    return cityCount;
}

// 分析标签统计
void AnalysisWindow::analyzeTagStatistics()
{
    QString html;

    // 文件1的标签统计
    QMap<QString, int> tagCount1 = countTags(contacts1);
    html += QString("<h3> %1 的标签统计 (%2 个联系人)</h3>")
                .arg(ui->file1NameLabel->text())
                .arg(contacts1.size());

    if (tagCount1.isEmpty()) {
        html += "<p><i>没有标签数据</i></p>";

    } else {
        html += "<table border='1' cellpadding='5' style='border-collapse: collapse; width: 100%;'>";
        html += "<tr style='background-color: #e3f2fd;'><th>标签</th><th>数量</th><th>比例</th></tr>";

        for (auto it = tagCount1.begin(); it != tagCount1.end(); ++it) {
            double percentage = (double)it.value() / contacts1.size() * 100;
            html += QString("<tr><td>%1</td><td align='center'>%2</td><td align='center'>%3%</td></tr>")
                        .arg(it.key())
                        .arg(it.value())
                        .arg(QString::number(percentage, 'f', 1));
        }
        html += "</table>";
    }

    // 文件2的标签统计
    QMap<QString, int> tagCount2 = countTags(contacts2);
    html += QString("<br><hr><h3> %1 的标签统计 (%2 个联系人)</h3>")
                .arg(ui->file2NameLabel->text())
                .arg(contacts2.size());

    if (tagCount2.isEmpty()) {
        html += "<p><i>没有标签数据</i></p>";
    } else {
        html += "<table border='1' cellpadding='5' style='border-collapse: collapse; width: 100%;'>";
        html += "<tr style='background-color: #e8f5e9;'><th>标签</th><th>数量</th><th>比例</th></tr>";

        for (auto it = tagCount2.begin(); it != tagCount2.end(); ++it) {
            double percentage = (double)it.value() / contacts2.size() * 100;
            html += QString("<tr><td>%1</td><td align='center'>%2</td><td align='center'>%3%</td></tr>")
                        .arg(it.key())
                        .arg(it.value())
                        .arg(QString::number(percentage, 'f', 1));
        }
        html += "</table>";
    }

    // 城市统计
    QMap<QString, int> cityCount1 = countCities(contacts1);
    QMap<QString, int> cityCount2 = countCities(contacts2);

    html += "<br><hr><h3> 城市分布统计</h3>";

    html += QString("<p><b>%1 的城市分布:</b> ").arg(ui->file1NameLabel->text());
    for (auto it = cityCount1.begin(); it != cityCount1.end(); ++it) {
        html += QString("%1(%2人) ").arg(it.key()).arg(it.value());
    }
    html += "</p>";

    html += QString("<p><b>%1 的城市分布:</b> ").arg(ui->file2NameLabel->text());
    for (auto it = cityCount2.begin(); it != cityCount2.end(); ++it) {
        html += QString("%1(%2人) ").arg(it.key()).arg(it.value());
    }
    html += "</p>";

    ui->tagTextBrowser->setHtml(html);
}

// 分析共同联系人
void AnalysisWindow::analyzeCommonContacts()
{
    QString html;

    // 查找共同联系人（基于姓名和电话）
    QList<Contact> commonContacts;

    for (const Contact &contact1 : contacts1) {
        for (const Contact &contact2 : contacts2) {
            // 如果姓名和电话相同，认为是同一人
            if (contact1.name == contact2.name && contact1.phone == contact2.phone) {
                commonContacts.append(contact1);
                break;
            }
        }
    }

    html += QString("<h3>🔗 共同联系人分析</h3>");
    html += QString("<p><b>%1</b>: %2 个联系人</p>")
                .arg(ui->file1NameLabel->text())
                .arg(contacts1.size());
    html += QString("<p><b>%1</b>: %2 个联系人</p>")
                .arg(ui->file2NameLabel->text())
                .arg(contacts2.size());
    html += QString("<p><b>共同联系人</b>: %1 个</p>")
                .arg(commonContacts.size());

    if (commonContacts.isEmpty()) {
        html += "<p><i>没有共同联系人</i></p>";
    } else {
        html += "<table border='1' cellpadding='5' style='border-collapse: collapse; width: 100%;'>";
        html += "<tr style='background-color: #fff3cd;'>"
                "<th>姓名</th><th>电话</th><th>城市</th>"
                "<th>标签 (文件1)</th><th>标签 (文件2)</th>"
                "</tr>";

        for (const Contact &commonContact : commonContacts) {
            // 找到文件2中的对应联系人
            Contact contact2;
            for (const Contact &c2 : contacts2) {
                if (c2.name == commonContact.name && c2.phone == commonContact.phone) {
                    contact2 = c2;
                    break;
                }
            }

            html += QString("<tr>"
                            "<td>%1</td>"
                            "<td>%2</td>"
                            "<td>%3</td>"
                            "<td>%4</td>"
                            "<td>%5</td>"
                            "</tr>")
                        .arg(commonContact.name)
                        .arg(commonContact.phone)
                        .arg(commonContact.city)
                        .arg(commonContact.tags.join(", "))
                        .arg(contact2.tags.join(", "));
        }
        html += "</table>";
    }

    ui->commonTextBrowser->setHtml(html);
}

// 计算共同联系人比例
double AnalysisWindow::calculateCommonContactRatio()
{
    int commonCount = 0;

    for (const Contact &contact1 : contacts1) {
        for (const Contact &contact2 : contacts2) {
            if (contact1.name == contact2.name && contact1.phone == contact2.phone) {
                commonCount++;
                break;
            }
        }
    }

    if (contacts1.size() == 0) return 0.0;
    return (double)commonCount / contacts1.size();
}

// 计算城市相似度
double AnalysisWindow::calculateCitySimilarity()
{
    QMap<QString, int> cityCount1 = countCities(contacts1);
    QMap<QString, int> cityCount2 = countCities(contacts2);

    int commonCityCount = 0;

    // 对每个城市，取两个文件中数量的最小值
    for (auto it = cityCount1.begin(); it != cityCount1.end(); ++it) {
        QString city = it.key();
        int count1 = it.value();
        int count2 = cityCount2.value(city, 0);

        commonCityCount += qMin(count1, count2);
    }

    if (contacts1.size() == 0) return 0.0;
    return (double)commonCityCount / contacts1.size();
}

// 计算标签相似度
double AnalysisWindow::calculateTagSimilarity()
{
    int commonWithTags = 0;

    // 对于每个共同联系人，检查是否有至少一个共同标签
    for (const Contact &contact1 : contacts1) {
        // 检查是否是共同联系人
        bool isCommon = false;
        Contact contact2;

        for (const Contact &c2 : contacts2) {
            if (contact1.name == c2.name && contact1.phone == c2.phone) {
                isCommon = true;
                contact2 = c2;
                break;
            }
        }

        if (isCommon) {
            // 检查是否有共同标签
            bool hasCommonTag = false;
            for (const QString &tag1 : contact1.tags) {
                if (contact2.tags.contains(tag1)) {
                    hasCommonTag = true;
                    break;
                }
            }

            if (hasCommonTag) {
                commonWithTags++;
            }
        }
    }

    if (contacts1.size() == 0) return 0.0;
    return (double)commonWithTags / contacts1.size();
}

// 计算社交关联度得分
double AnalysisWindow::calculateSocialRelationScore()
{
    double commonRatio = calculateCommonContactRatio();
    double citySimilarity = calculateCitySimilarity();
    double tagSimilarity = calculateTagSimilarity();

    qDebug() << "计算得分:";
    qDebug() << "  共同联系人比例:" << commonRatio;
    qDebug() << "  城市相似度:" << citySimilarity;
    qDebug() << "  标签相似度:" << tagSimilarity;

    double score = 0.5 * commonRatio + 0.3 * citySimilarity + 0.2 * tagSimilarity;
    return score;
}

// 获取关系级别
QString AnalysisWindow::getRelationLevel(double score)
{
    if (score >= 0.8) return "非常亲密";
    else if (score >= 0.6) return "比较亲密";
    else if (score >= 0.4) return "一般关系";
    else if (score >= 0.2) return "较弱关系";
    else return "几乎无关";
}

// 分析社交关联度
void AnalysisWindow::analyzeSocialRelation()
{
    QString html;

    // A对B的关联度
    double scoreAB = calculateSocialRelationScore();
    QString levelAB = getRelationLevel(scoreAB);

    // 交换contacts1和contacts2计算B对A的关联度
    qSwap(contacts1, contacts2);
    double scoreBA = calculateSocialRelationScore();
    QString levelBA = getRelationLevel(scoreBA);
    qSwap(contacts1, contacts2); // 恢复原状

    // 获取详细数据用于显示
    double commonRatio = calculateCommonContactRatio();
    double citySimilarity = calculateCitySimilarity();
    double tagSimilarity = calculateTagSimilarity();

    QMap<QString, int> cityCount1 = countCities(contacts1);
    QMap<QString, int> cityCount2 = countCities(contacts2);

    html += "<h3>社交关联度分析</h3>";

    // 详细计算过程
    html += QString("<h4> %1 → %2 的计算过程:</h4>")
                .arg(ui->file1NameLabel->text())
                .arg(ui->file2NameLabel->text());

    html += "<table border='1' cellpadding='5' style='border-collapse: collapse; width: 80%;'>";
    html += "<tr style='background-color: #f8f9fa;'>"
            "<th>计算项目</th><th>计算公式</th><th>结果</th><th>权重</th><th>加权值</th>"
            "</tr>";

    html += QString("<tr>"
                    "<td>共同联系人比例</td>"
                    "<td>共同联系人数 / A联系人数</td>"
                    "<td align='center'>%1 / %2 = %3</td>"
                    "<td align='center'>0.5</td>"
                    "<td align='center'>%4</td>"
                    "</tr>")
                .arg(int(commonRatio * contacts1.size()))
                .arg(contacts1.size())
                .arg(QString::number(commonRatio, 'f', 3))
                .arg(QString::number(0.5 * commonRatio, 'f', 3));

    html += QString("<tr>"
                    "<td>城市相似度</td>"
                    "<td>共同城市联系人数 / A联系人数</td>"
                    "<td align='center'>%1 / %2 = %3</td>"
                    "<td align='center'>0.3</td>"
                    "<td align='center'>%4</td>"
                    "</tr>")
                .arg(int(citySimilarity * contacts1.size()))
                .arg(contacts1.size())
                .arg(QString::number(citySimilarity, 'f', 3))
                .arg(QString::number(0.3 * citySimilarity, 'f', 3));

    html += QString("<tr>"
                    "<td>标签相似度</td>"
                    "<td>有共同标签人数 / A联系人数</td>"
                    "<td align='center'>%1 / %2 = %3</td>"
                    "<td align='center'>0.2</td>"
                    "<td align='center'>%4</td>"
                    "</tr>")
                .arg(int(tagSimilarity * contacts1.size()))
                .arg(contacts1.size())
                .arg(QString::number(tagSimilarity, 'f', 3))
                .arg(QString::number(0.2 * tagSimilarity, 'f', 3));

    html += QString("<tr style='background-color: #e8f5e9; font-weight: bold;'>"
                    "<td colspan='4' align='right'>总得分</td>"
                    "<td align='center'>%1</td>"
                    "</tr>")
                .arg(QString::number(scoreAB, 'f', 3));
    html += "</table>";

    // 城市分布详情
    html += "<h4>城市分布详情:</h4>";
    html += QString("<p><b>%1:</b> ").arg(ui->file1NameLabel->text());
    for (auto it = cityCount1.begin(); it != cityCount1.end(); ++it) {
        html += QString("%1(%2人) ").arg(it.key()).arg(it.value());
    }
    html += "</p>";

    html += QString("<p><b>%1:</b> ").arg(ui->file2NameLabel->text());
    for (auto it = cityCount2.begin(); it != cityCount2.end(); ++it) {
        html += QString("%1(%2人) ").arg(it.key()).arg(it.value());
    }
    html += "</p>";

    // 结果显示
    html += "<br><hr><h3>分析结果</h3>";

    html += "<table border='1' cellpadding='10' style='border-collapse: collapse; width: 100%;'>";
    html += "<tr style='background-color: #e3f2fd;'>"
            "<th>关系方向</th><th>关联度得分</th><th>关系级别</th><th>强度范围</th>"
            "</tr>";

    html += QString("<tr>"
                    "<td><b>%1 → %2</b></td>"
                    "<td align='center' style='font-size: 24px; color: #2196F3;'>%3</td>"
                    "<td align='center' style='font-size: 18px;'>%4</td>"
                    "<td align='center'>0.8-1.0: 非常亲密<br>"
                    "0.6-0.8: 比较亲密<br>"
                    "0.4-0.6: 一般关系<br>"
                    "0.2-0.4: 较弱关系<br>"
                    "0.0-0.2: 几乎无关</td>"
                    "</tr>")
                .arg(ui->file1NameLabel->text())
                .arg(ui->file2NameLabel->text())
                .arg(QString::number(scoreAB, 'f', 3))
                .arg(levelAB);

    html += QString("<tr>"
                    "<td><b>%1 → %2</b></td>"
                    "<td align='center' style='font-size: 24px; color: #4CAF50;'>%3</td>"
                    "<td align='center' style='font-size: 18px;'>%4</td>"
                    "<td align='center'>同上</td>"
                    "</tr>")
                .arg(ui->file2NameLabel->text())
                .arg(ui->file1NameLabel->text())
                .arg(QString::number(scoreBA, 'f', 3))
                .arg(levelBA);

    html += "</table>";

    // 总结
    html += "<br><hr><h4>💡 分析总结:</h4>";
    html += QString("<p>根据分析，%1 和 %2 之间的社交关系为 <b>%3</b>。</p>")
                .arg(ui->file1NameLabel->text())
                .arg(ui->file2NameLabel->text())
                .arg(scoreAB > scoreBA ? levelAB : levelBA);

    if (scoreAB >= 0.6 || scoreBA >= 0.6) {
        html += "<p style='color: #d32f2f;'>提示: Best Friend!</p>";
    } else if (scoreAB >= 0.4 || scoreBA >= 0.4) {
        html += "<p style='color: #f57c00;'>提示: 你们有一般的社会关系，有一定共同点。</p>";
    } else {
        html += "<p style='color: #757575;'>提示: 你们的社会关系较弱，共同点较少。</p>";
    }

    ui->relationTextBrowser->setHtml(html);
}

void AnalysisWindow::onBackButtonClicked()
{
    this->close();
    if (parentWidget()) {
        parentWidget()->show();
    }
}
