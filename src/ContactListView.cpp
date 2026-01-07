#pragma execution_character_set("utf-8")

#include "ContactListView.h"
#include "imgui.h"
#include <algorithm>
#include <string>
#include <sstream>



struct ViewState {

	int searchType = 0;
	char searchBuffer[128] = "";
	std::vector<int> filteredIndices;
	bool isFiltered = false;

	bool showEditModal = false;
	bool isCreatingNew = false;
	Contact editingContact;
	int editingIndex = -1;

	char editName[64];
	char editGender[16];
	char editAge[8];
	char editPhone[32];
	char editCity[64];
	char editCompany[128];
	char editAddress[128];
	char editTags[256];
};
//.....。。。。。。。。。。。

static ViewState g_State;

void OpenEditModal(const Contact& contact, int index, bool isNew) {
	g_State.showEditModal = true;
	g_State.isCreatingNew = isNew;
	g_State.editingContact = contact;
	g_State.editingIndex = index;

	//标注。
	// 把 string 转成 char* 供 ImGui 输入框使用
	strcpy_s(g_State.editName, contact.name.c_str());
	strcpy_s(g_State.editGender, contact.gender.c_str());
	strcpy_s(g_State.editAge, contact.age.c_str());
	strcpy_s(g_State.editCity, contact.city.c_str());
	strcpy_s(g_State.editCompany, contact.company.c_str());
	strcpy_s(g_State.editAddress, contact.address.c_str());

	// 标签转字符串 (空格分隔)
	std::string tagsStr;
	for (int tid : contact.tagIDs) {
		if (tid >= 0 && tid < Contact::globalIdToTag.size())
			tagsStr += Contact::globalIdToTag[tid] + " ";
	}
	strcpy_s(g_State.editTags, tagsStr.c_str());
}

void PerformSearch(const std::vector<Contact>& contacts) {
	g_State.filteredIndices.clear();
	std::string key = g_State.searchBuffer;

	if(key.empty()) {
		g_State.isFiltered = false;
		return;
	}
	g_State.isFiltered = true;
	for (int i = 0; i < contacts.size(); i++) {
		const auto& c = contacts[i];
		bool match = false;

		if (g_State.searchType == 0) match = (c.name.find(key) != std::string::npos);       // 姓名
		else if (g_State.searchType == 1) match = (c.city.find(key) != std::string::npos);  // 城市
		else if (g_State.searchType == 2) {                                                 // 标签
			for (int tid : c.tagIDs) {
				if (tid >= 0 && tid < Contact::globalIdToTag.size()) {
					if (Contact::globalIdToTag[tid].find(key) != std::string::npos)
						match = true;
						break;
				}
			}
		}
		else if (g_State.searchType == 3) match = (c.phone.find(key) != std::string::npos); // 电话

		if (match) {
			g_State.filteredIndices.push_back(i);
		}
	}

}


void RenderContactListView(SocialAnalyzer& app) {

	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);

	ImGui::Begin("ContactSystemView", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

	if (ImGui::Button("<< 返回主菜单")) {
		app.currentState = AppState::Menu;
	}
	ImGui::SameLine();
	ImGui::Text("当前管理: %s | 总人数: %d", app.file1Name.c_str(), app.contacts1.size());

	ImGui::SameLine(ImGui::GetWindowWidth() - 150);
	
	static char searchBuffer[128] = "";
	ImGui::InputTextWithHint("##Search", "搜索姓名/电话...", searchBuffer, IM_ARRAYSIZE(searchBuffer));
	ImGui::SameLine();
	if (ImGui::Button("➕ 新建联系人", ImVec2(120, 0))) {
		// TODO: 弹出新建窗口
		Contact newC;
		int maxID = 0;
		for (auto& c : app.contacts1) if (c.id > maxID) maxID = c.id;
		newC.id = maxID + 1;
		OpenEditModal(newC, -1, true);
	}

	ImGui::Separator();
	ImGui::Spacing();



	ImGui::BeginGroup();
	{
		ImGui::SetNextItemWidth(100);
		const char* types[] = { "姓名", "城市", "标签", "电话" };
		ImGui::Combo("##Type", &g_State.searchType, types, IM_ARRAYSIZE(types));

		ImGui::SameLine();
		ImGui::SetNextItemWidth(300);
		ImGui::InputTextWithHint("##SearchInput", "输入查询关键词...", g_State.searchBuffer, IM_ARRAYSIZE(g_State.searchBuffer));

		ImGui::SameLine();
		if (ImGui::Button("🔍 查询")) {
			PerformSearch(app.contacts1);
		}

		ImGui::SameLine();
		if (ImGui::Button("🔄 重置")) {
			g_State.searchBuffer[0] = '\0';
			g_State.isFiltered = false;
		}
	}
	ImGui::EndGroup();

	ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();


	const std::vector<int>* indicesPtr = nullptr;
	int totalItems = 0;

	if (g_State.isFiltered) {
		totalItems = g_State.filteredIndices.size();
		ImGui::TextColored(ImVec4(0.2f, 0.8f, 0.2f, 1.0f), "查询结果: 找到 %d 个联系人", totalItems);
	}
	else {
		totalItems = app.contacts1.size();
		ImGui::Text("共 %d 个联系人", totalItems);
	}

	ImGui::BeginChild("ListRegion", ImVec2(0, 0), true);

	if (ImGui::BeginTable("ContactTable", 8, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY)) {

		ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed, 40.0f);
		ImGui::TableSetupColumn("姓名", ImGuiTableColumnFlags_WidthFixed, 100.0f);
		ImGui::TableSetupColumn("电话", ImGuiTableColumnFlags_WidthFixed, 120.0f);
		ImGui::TableSetupColumn("城市", ImGuiTableColumnFlags_WidthFixed, 80.0f);
		ImGui::TableSetupColumn("单位", ImGuiTableColumnFlags_WidthFixed, 120.0f);
		ImGui::TableSetupColumn("住址", ImGuiTableColumnFlags_WidthFixed, 150.0f);

		ImGui::TableSetupColumn("标签", ImGuiTableColumnFlags_WidthStretch);
		ImGui::TableSetupColumn("操作", ImGuiTableColumnFlags_WidthFixed, 120.0f);
		ImGui::TableSetupScrollFreeze(0, 1);
		ImGui::TableHeadersRow();

		for (int i = 0; i < totalItems; i++) {
			// 获取真实的 contact 引用和索引
			int realIndex = g_State.isFiltered ? g_State.filteredIndices[i] : i;
			Contact& c = app.contacts1[realIndex];

			ImGui::TableNextRow();

			ImGui::TableNextColumn(); ImGui::Text("%d", c.id);
			ImGui::TableNextColumn(); ImGui::Text("%s", c.name.c_str());
			ImGui::TableNextColumn(); ImGui::Text("%s", c.phone.c_str());
			ImGui::TableNextColumn(); ImGui::Text("%s", c.city.c_str());
			ImGui::TableNextColumn(); ImGui::Text("%s", c.company.c_str()); 
			ImGui::TableNextColumn(); ImGui::Text("%s", c.address.c_str());

			ImGui::TableNextColumn();
			// 简单拼接标签显示
			for (int tid : c.tagIDs) {
				if (tid >= 0 && tid < Contact::globalIdToTag.size()) {
					ImGui::TextDisabled("%s ", Contact::globalIdToTag[tid].c_str());
					ImGui::SameLine();
				}
			}

			ImGui::TableNextColumn();
			ImGui::PushID(realIndex);

			// "管理" 按钮 -> 打开编辑弹窗
			if (ImGui::Button("管理")) {
				OpenEditModal(c, realIndex, false);
			}

			// "删除" 按钮 (直接变红)
			ImGui::SameLine();
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));
			if (ImGui::Button("X")) {
				// 删除逻辑
				app.contacts1.erase(app.contacts1.begin() + realIndex);
				// 重新保存文件
				app.saveContacts("./Data/" + app.file1Name, 1);
				// 如果在搜索状态，简单处理：重置搜索防止索引越界
				if (g_State.isFiltered) PerformSearch(app.contacts1);
			}
			ImGui::PopStyleColor();

			ImGui::PopID();
		}

		ImGui::EndTable();
	}
	ImGui::EndChild();




	if (g_State.showEditModal) {
		ImGui::OpenPopup("编辑联系人");
	}

	if (ImGui::BeginPopupModal("编辑联系人", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

		ImGui::Text("ID: %d (自动生成)", g_State.editingContact.id);
		ImGui::Separator();

		// 表单区域
		ImGui::InputText("姓名", g_State.editName, 64);
		ImGui::InputText("性别", g_State.editGender, 16);
		ImGui::InputText("年龄", g_State.editAge, 8);
		ImGui::InputText("电话", g_State.editPhone, 32);
		ImGui::InputText("城市", g_State.editCity, 64);
		ImGui::InputText("单位", g_State.editCompany, 128);
		ImGui::InputText("住址", g_State.editAddress, 128);
		ImGui::InputText("标签 (空格分隔)", g_State.editTags, 256);

		ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();

		if (ImGui::Button("保存", ImVec2(100, 0))) {
			// 1. 写回数据到 Contact 对象
			Contact& c = g_State.editingContact;
			c.name = g_State.editName;
			c.gender = g_State.editGender;
			c.age = g_State.editAge;
			c.phone = g_State.editPhone;
			c.city = g_State.editCity;
			c.company = g_State.editCompany;
			c.address = g_State.editAddress;

			// 解析标签 string -> vector
			c.tagIDs.clear();
			std::stringstream ss(g_State.editTags);
			std::string tag;
			while (ss >> tag) {
				int tid = Contact::GetOrCreateTagID(tag);
				c.tagIDs.push_back(tid);
			}

			// 2. 更新到主列表
			if (g_State.isCreatingNew) {
				app.contacts1.push_back(c);
			}
			else {
				app.contacts1[g_State.editingIndex] = c;
			}

			// 3. 保存到文件 (持久化)
			app.saveContacts("./Data/" + app.file1Name, 1);

			// 4. 关闭弹窗
			g_State.showEditModal = false;
			ImGui::CloseCurrentPopup();

			// 刷新搜索结果（如果正在搜索）
			if (g_State.isFiltered) PerformSearch(app.contacts1);
		}

		ImGui::SameLine();
		if (ImGui::Button("取消", ImVec2(100, 0))) {
			g_State.showEditModal = false;
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}

	ImGui::End();
}
