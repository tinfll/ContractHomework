#pragma execution_character_set("utf-8")
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "SocialAnalyzer.h"
#include "ContactListView.h"
#include "Contact.h"

#include <iostream>
#include <fstream>
#include <filesystem> // C++17 文件系统
#include <algorithm>
#include <iomanip>    
#include <sstream>

namespace fs = std::filesystem;



void SocialAnalyzer::scanDirectory(const std::string& directoryPath) {
    availableFiles.clear();
    // 检查目录是否存在
    if (fs::exists(directoryPath) && fs::is_directory(directoryPath)) {
        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            if (entry.path().extension() == ".txt") {
                // 只存文件名，例如 "contacts_zhang.txt"
                availableFiles.push_back(entry.path().filename().string());
            }
        }
    }
    else 
        // 如果目录不存在
        std::cerr << "警告: Data 目录不存在: " << directoryPath << std::endl;
}

bool SocialAnalyzer::loadContactFile(const std::string& fullPath, int slot) {
    std::ifstream file(fullPath);
    if (!file.is_open()) return false;

    std::vector<Contact>* targetList = (slot == 1) ? &contacts1 : &contacts2;
    targetList->clear();

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        // 去除行尾回
        if (!line.empty() && line.back() == '\r') line.pop_back();

        Contact c;
        if (c.parseFromString(line)) {
            targetList->push_back(c);
        }
    }
    return true;
}



std::map<std::string, int> SocialAnalyzer::countTags(const std::vector<Contact>& contacts) {
    std::map<std::string, int> counts;
    for (const auto& c : contacts) {
        for (int tid : c.tagIDs) {
            if (tid >= 0 && tid < Contact::globalIdToTag.size()) {
                std::string tagName = Contact::globalIdToTag[tid];
                if (!tagName.empty()) counts[tagName]++;
            }
        }
    }
    return counts;
}

std::map<std::string, int> SocialAnalyzer::countCities(const std::vector<Contact>& contacts) {
    std::map<std::string, int> counts;
    for (const auto& c : contacts) {
        if (!c.city.empty()) counts[c.city]++;
    }
    return counts;
}

double SocialAnalyzer::calculateCommonRatio() {
    if (contacts1.empty()) return 0.0;
    int commonCount = 0;
    for (const auto& c1 : contacts1) {
        for (const auto& c2 : contacts2) {
            if (c1.name == c2.name && c1.phone == c2.phone) {
                commonCount++;
                break;
            }
        }
    }
    return (double)commonCount / contacts1.size();
}

double SocialAnalyzer::calculateCitySimilarity() {
    if (contacts1.empty()) return 0.0;
    auto map1 = countCities(contacts1);
    auto map2 = countCities(contacts2);
    int commonCityCount = 0;

    for (auto const& [city, count1] : map1) {
        if (map2.count(city)) {
            commonCityCount += std::min(count1, map2[city]);
        }
    }
    return (double)commonCityCount / contacts1.size();
}

double SocialAnalyzer::calculateTagSimilarity() {
    if (contacts1.empty()) return 0.0;
    int commonWithTags = 0;

    // 逻辑：如果是共同联系人，且有至少一个共同标签
    for (const auto& c1 : contacts1) {
        bool isCommon = false;
        Contact c2_found;
        for (const auto& c2 : contacts2) {
            if (c1.name == c2.name && c1.phone == c2.phone) {
                isCommon = true;
                c2_found = c2;
                break;
            }
        }

        if (isCommon) {
            bool hasCommonTag = false;
            for (int tagID :c1.tagIDs) {
                //比较id速度更快
                if (std::find(c2_found.tagIDs.begin(), c2_found.tagIDs.end(), tagID) != c2_found.tagIDs.end()) {
                    hasCommonTag = true;
                    break;
                }
            }
            if (hasCommonTag) commonWithTags++;
        }
    }
    return (double)commonWithTags / contacts1.size();
}

double SocialAnalyzer::calculateSocialScore() {
    return 0.5 * calculateCommonRatio() + 0.3 * calculateCitySimilarity() + 0.2 * calculateTagSimilarity();
}

std::string SocialAnalyzer::getRelationLevel(double score) {
    if (score >= 0.8) return "非常亲密";
    if (score >= 0.6) return "比较亲密";
    if (score >= 0.4) return "一般关系";
    if (score >= 0.2) return "较弱关系";
    return "几乎无关";
}


//界面

//全屏
void SetupFullScreenWindow(const char* name) {
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::Begin(name, nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
}

// 主菜单
void RenderMainMenu(GLFWwindow* window, SocialAnalyzer& app) {
    SetupFullScreenWindow("MainMenu");

    ImGui::Spacing(); ImGui::Spacing();

        ImGui::SetWindowFontScale(2.0f);
        const char* title = "ETH人际管理系统";
        float titleW = ImGui::CalcTextSize(title).x;
        ImGui::SetCursorPosX((ImGui::GetWindowWidth() - titleW) * 0.5f);
        ImGui::Text("%s", title);
        ImGui::SetWindowFontScale(1.0f);

        ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();

   
        ImGui::BeginChild("CenterGroup", ImVec2(400, 300), true);
        {
            ImGui::TextDisabled("功能选择");
            ImGui::Separator();
            ImGui::Spacing();

            float btnW = 250.0f;
            float cursorX = (400 - btnW) * 0.5f;

         
            ImGui::SetCursorPosX(cursorX);
            if (ImGui::Button("查看/管理单个通讯录", ImVec2(btnW, 40))) {
                app.scanDirectory("./Data");
                app.selectedFileIndex1 = -1;
                app.isSingleMode = true;
                app.currentState = AppState::SelectFiles;
            }

            ImGui::Spacing();

            ImGui::SetCursorPosX(cursorX);
            if (ImGui::Button("双人社交关系分析 (Compare)", ImVec2(btnW, 40))) {
                app.scanDirectory("./Data");
                app.selectedFileIndex1 = -1;
                app.selectedFileIndex2 = -1;

                app.isSingleMode = false;
                app.currentState = AppState::SelectFiles;
            }

            ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();

            // 退出按钮
            ImGui::SetCursorPosX(cursorX);
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));
            if (ImGui::Button("退出系统", ImVec2(btnW, 40))) {
                glfwSetWindowShouldClose(window, true);
            }
            ImGui::PopStyleColor();
        }

        ImGui::EndChild();
    
    ImGui::End();
}

// 界面2: 文件选择器
void RenderFileSelector(SocialAnalyzer& app) {
    SetupFullScreenWindow("FileSelector");

    if (app.isSingleMode) {
        ImGui::Text("请选择要管理的通讯录文件：");
    }
    else {
        ImGui::Text("请选择要进行对比分析的两个通讯录文件：");
    }
    ImGui::Separator();




    if (app.availableFiles.empty()) {
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "错误：在 ./Data/ 目录下未找到 .txt 文件！");
        if (ImGui::Button("返回主菜单")) app.currentState = AppState::Menu;
        ImGui::End();
        return;
    }

    ImGui::Separator();
    if (app.availableFiles.empty()) {
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "错误：在 ./Data/ 目录下未找到 .txt 文件！");
        if (ImGui::Button("返回主菜单")) app.currentState = AppState::Menu;
        ImGui::End();
        return;
    }



    // 辅助 lambda：下拉框
    auto FileCombo = [&](const char* label, int* currentIdx) {
        const char* preview = (*currentIdx >= 0 && *currentIdx < app.availableFiles.size())
            ? app.availableFiles[*currentIdx].c_str()
            : "请选择文件...";

        if (ImGui::BeginCombo(label, preview)) {
            for (int i = 0; i < app.availableFiles.size(); i++) {
                const bool is_selected = (*currentIdx == i);
                if (ImGui::Selectable(app.availableFiles[i].c_str(), is_selected))
                    *currentIdx = i;
                if (is_selected) ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
        };

    ImGui::Spacing();



    if (app.isSingleMode) {
        // 【单人模式】只画一个下拉框
        ImGui::Text("目标通讯录:");
        FileCombo("##File1", &app.selectedFileIndex1);
    }
    else {
        // 【双人模式】画两个下拉框
        ImGui::Text("通讯录 A:");
        FileCombo("##File1", &app.selectedFileIndex1);
        ImGui::Spacing();
        ImGui::Text("通讯录 B:");
        FileCombo("##File2", &app.selectedFileIndex2);
    }

    ImGui::Spacing(); ImGui::Spacing();

    // 确认按钮
    // 确认按钮逻辑
    bool canProceed = false;
    if (app.isSingleMode) {
        canProceed = (app.selectedFileIndex1 >= 0); // 单人只要选了第一个就行
    }
    else {
        canProceed = (app.selectedFileIndex1 >= 0 && app.selectedFileIndex2 >= 0); // 双人要选俩
    }

    if (!canProceed) ImGui::BeginDisabled();

    // 按钮文字根据模式变化
    if (ImGui::Button(app.isSingleMode ? "进入管理系统" : "开始对比分析", ImVec2(150, 40))) {

        // 加载第一个文件 (无论单双都要加载)
        std::string name1 = app.availableFiles[app.selectedFileIndex1];
        bool ok1 = app.loadContactFile("./Data/" + name1, 1);

        if (app.isSingleMode) {
            // ---> 单人跳转逻辑
            if (ok1) {
                app.file1Name = name1;
                app.currentState = AppState::ViewSystem; // 跳转到空界面
            }
        }
        else {
            // ---> 双人跳转逻辑
            std::string name2 = app.availableFiles[app.selectedFileIndex2];
            bool ok2 = app.loadContactFile("./Data/" + name2, 2);
            if (ok1 && ok2) {
                app.file1Name = name1;
                app.file2Name = name2;
                app.currentState = AppState::AnalysisResult; // 跳转到分析结果
            }
        }
    }
    if (!canProceed) ImGui::EndDisabled();

    ImGui::SameLine();
    if (ImGui::Button("取消", ImVec2(100, 40))) {
        app.currentState = AppState::Menu;
    }

    ImGui::End();

}


void RenderAnalysisResult(SocialAnalyzer& app) {
    SetupFullScreenWindow("AnalysisResult");

    // 顶部导航
    if (ImGui::Button("<< 返回主菜单")) {
        app.currentState = AppState::Menu;
    }
    ImGui::SameLine();
    ImGui::Text("分析对象: %s vs %s", app.file1Name.c_str(), app.file2Name.c_str());
    ImGui::Separator();

    if (ImGui::BeginTabBar("AnalysisTabs")) {

        // --- 标签页 1: 概览 & 评分 ---
        if (ImGui::BeginTabItem("社交关联度")) {
            double score = app.calculateSocialScore();
            std::string level = app.getRelationLevel(score);

            ImGui::Spacing();
            ImGui::Text("综合关联度得分: %.3f", score);
            ImGui::TextColored(ImVec4(0, 1, 0, 1), "关系评级: %s", level.c_str());

            // 绘制大进度条
            ImGui::ProgressBar((float)score, ImVec2(-1, 30.0f));

            ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();

            // 详细计算表
            ImGui::Text("计算细节:");
            if (ImGui::BeginTable("CalcTable", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
                ImGui::TableSetupColumn("维度");
                ImGui::TableSetupColumn("权重");
                ImGui::TableSetupColumn("数值");
                ImGui::TableSetupColumn("加权贡献");
                ImGui::TableHeadersRow();

                auto Row = [](const char* name, double weight, double val) {
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn(); ImGui::Text("%s", name);
                    ImGui::TableNextColumn(); ImGui::Text("%.1f", weight);
                    ImGui::TableNextColumn(); ImGui::Text("%.3f", val);
                    ImGui::TableNextColumn(); ImGui::Text("%.3f", val * weight);
                    };

                Row("共同好友", 0.5, app.calculateCommonRatio());
                Row("城市重合", 0.3, app.calculateCitySimilarity());
                Row("标签相似", 0.2, app.calculateTagSimilarity());

                ImGui::EndTable();
            }

            ImGui::EndTabItem();
        }

        // --- 标签页 2: 共同联系人 ---
        if (ImGui::BeginTabItem("🔗 共同联系人")) {
            if (ImGui::BeginTable("CommonTable", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
                ImGui::TableSetupColumn("姓名");
                ImGui::TableSetupColumn("电话");
                ImGui::TableSetupColumn("城市");
                ImGui::TableHeadersRow();

                for (const auto& c1 : app.contacts1) {
                    for (const auto& c2 : app.contacts2) {
                        if (c1.name == c2.name && c1.phone == c2.phone) {
                            ImGui::TableNextRow();
                            ImGui::TableNextColumn(); ImGui::Text("%s", c1.name.c_str());
                            ImGui::TableNextColumn(); ImGui::Text("%s", c1.phone.c_str());
                            ImGui::TableNextColumn(); ImGui::Text("%s", c1.city.c_str());
                            break;
                        }
                    }
                }
                ImGui::EndTable();
            }
            ImGui::EndTabItem();
        }

        // --- 标签页 3: 标签统计 (简单展示) ---
        if (ImGui::BeginTabItem("📊 标签统计")) {
            auto DrawTags = [](const char* title, std::map<std::string, int> counts) {
                ImGui::Text("%s", title);
                if (ImGui::BeginTable(title, 2, ImGuiTableFlags_Borders)) {
                    ImGui::TableSetupColumn("标签");
                    ImGui::TableSetupColumn("人数");
                    ImGui::TableHeadersRow();
                    for (auto const& [tag, num] : counts) {
                        ImGui::TableNextRow();
                        ImGui::TableNextColumn(); ImGui::Text("%s", tag.c_str());
                        ImGui::TableNextColumn(); ImGui::Text("%d", num);
                    }
                    ImGui::EndTable();
                }
                };

            ImGui::Columns(2);
            DrawTags(app.file1Name.c_str(), app.countTags(app.contacts1));
            ImGui::NextColumn();
            DrawTags(app.file2Name.c_str(), app.countTags(app.contacts2));
            ImGui::Columns(1);

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
    ImGui::End();
}




void SocialAnalyzer::saveContacts(const std::string& fullPath, int slot) {
    std::ofstream file(fullPath);
    if (!file.is_open()) {
        std::cerr << "无法打开文件进行写入: " << fullPath << std::endl;
        return;
    }

    // 根据 slot 决定保存哪一组数据
    const std::vector<Contact>& targetList = (slot == 1) ? contacts1 : contacts2;

    for (const auto& c : targetList) {
        // 写入基本信息
        file << c.id << " "
            << c.name << " "
            << c.gender << " "
            << c.age << " "
            << c.phone << " "
            << c.city << " "
            << c.company << " "
            << c.address;

        // 写入标签
        for (int tid : c.tagIDs){
            if (tid >= 0 && tid < Contact::globalIdToTag.size()) {
                std::string tagName = Contact::globalIdToTag[tid];
                if (!tagName.empty()) {
                    file << " " << tagName;
                }
            }
        }
        file << "\n";
    }
    file.close();
    std::cout << "已保存 " << targetList.size() << " 个联系人到 " << fullPath << std::endl;
}


// 全局调度
void RenderAppUI(GLFWwindow* window, SocialAnalyzer& app) {
    switch (app.currentState) {
    case AppState::Menu:
        RenderMainMenu(window, app);
        break;
    case AppState::SelectFiles:
        RenderFileSelector(app);
        break;
	case AppState::ViewSystem:
        RenderContactListView(app);
		break;
    case AppState::AnalysisResult:
        RenderAnalysisResult(app);
        break;
    }
}


