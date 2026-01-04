#pragma once
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include "Contact.h"

// 定义程序的状态
enum class AppState {
    Menu,               // 主菜单
    SelectFiles,        // 新增：选择两个文件进行对比
    AnalysisResult,      // 分析结果展示
    ViewSystem
};

class SocialAnalyzer {
public:
    AppState currentState = AppState::Menu;

    bool isSingleMode = false;

    // 当前加载的联系人数据
    std::vector<Contact> contacts1;
    std::vector<Contact> contacts2;

    // 当前分析的文件名
    std::string file1Name;
    std::string file2Name;

    // 文件选择相关
    std::vector<std::string> availableFiles; // 扫描到的 txt 文件列表
    int selectedFileIndex1 = -1; // 下拉框选中的索引
    int selectedFileIndex2 = -1;

    // --- 核心功能 ---
    // 扫描 Data 文件夹下的 txt 文件
    void scanDirectory(const std::string& directoryPath);

    // 加载指定文件到 slot (1 或 2)
    bool loadContactFile(const std::string& fullPath, int slot);


    // ---2nd: 统计与计算算法 ---
    std::map<std::string, int> countTags(const std::vector<Contact>& contacts);
    std::map<std::string, int> countCities(const std::vector<Contact>& contacts);

    double calculateCommonRatio();
    double calculateCitySimilarity();
    double calculateTagSimilarity();
    double calculateSocialScore();
    std::string getRelationLevel(double score);
    void saveContacts(const std::string& fullPath, int slot);
};

// 渲染入口函数
struct GLFWwindow;
void RenderAppUI(GLFWwindow* window, SocialAnalyzer& app);