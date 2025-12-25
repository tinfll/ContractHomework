#ifndef CONTACT_H
#define CONTACT_H


#include <QString>
#include <QStringList>

struct Contact
{
    int id;               // 编号
    QString name;         // 姓名
    QString gender;       // 性别
    QString age;          // 年龄
    QString phone;        // 电话
    QString city;         // 所在城市
    QString company;      // 所在单位
    QString address;      // 住址
    QStringList tags;     // 标签列表（如：家人、同事、朋友、同学）

    Contact() : id(0) {}

    bool parseFromString(const QString &line);

    QString toString() const;

    QString getShortInfo() const;
};


#endif // CONTACT_H
