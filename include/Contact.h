#pragma once
#ifndef CONTACT_H
#define CONTACT_H

#include <string>
#include <vector>
#include <map>

struct Contact
{
    int id;                   // 编号
    std::string name;         // 姓名
    std::string gender;       // 性别
    std::string age;          // 年龄
    std::string phone;        // 电话
    std::string city;         // 所在城市
    std::string company;      // 所在单位
    std::string address;    // 住址



    //::vector<std::string> tags; // 标签列表
    std::vector<int> tagIDs;

    Contact() : id(0) {}

    static std::map<std::string,  int> globalTagToId;
    static std::vector<std::string> globalIdToTag;
    
    static int GetOrCreateTagID(const std::string& Tag);

    bool parseFromString(const std::string& line);

    // 转回字符串用于保存
    std::string toString() const;

    // 获取简短信息 (用于UI列表显示)
    std::string getShortInfo() const;

    std::vector<std::string> getTagStrings() const;
    
    int GetTagID(const std::string& tag);
};

#endif // CONTACT_H

