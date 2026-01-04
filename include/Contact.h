#pragma once
#ifndef CONTACT_H
#define CONTACT_H

#include <string>
#include <vector>

struct Contact
{
    int id;                   // 编号
    std::string name;         // 姓名
    std::string gender;       // 性别
    std::string age;          // 年龄
    std::string phone;        // 电话
    std::string city;         // 所在城市
    std::string company;      // 所在单位
    std::string address;      // 住址
    std::vector<std::string> tags; // 标签列表

    Contact() : id(0) {}

    
    bool parseFromString(const std::string& line);

    // 转回字符串用于保存
    std::string toString() const;

    // 获取简短信息 (用于UI列表显示)
    std::string getShortInfo() const;
};

#endif // CONTACT_H