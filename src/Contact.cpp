#include "Contact.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>


std::map<std::string, int> Contact::globalTagToId;
std::vector<std::string> Contact::globalIdToTag;


int Contact::GetOrCreateTagID(const std::string& tag) {
	if (globalTagToId.find(tag) == globalTagToId.end()) {
		int newId = (int)globalIdToTag.size();
		globalIdToTag.push_back(tag);
		globalTagToId[tag] = newId;
		return newId;
	}
	else return globalTagToId[tag];
}


bool Contact::parseFromString(const std::string& line) {

	std::stringstream ss(line);
	std::string segment;
	std::vector<std::string> parts;

	while (ss >> segment) {
		parts.push_back(segment);
	}

	if (parts.size() < 7) {
		std::cerr << "错误: 数据格式不足 -> " << line << std::endl;
		return false;
	}

	try {
		id = std::stoi(parts[0]);
	}
	catch (...) {
		std::cerr << "错误: ID不是数字 -> " << parts[0] << std::endl;
		return false;
	}


	name = parts[1];
	gender = parts[2];
	age = parts[3];
	phone = parts[4];
	city = parts[5];
	company = parts[6];
	address = parts[7];

	tagIDs.clear();
	for (size_t i = 8; i < parts.size(); i++) {
		int tid = GetOrCreateTagID(parts[i]);
		tagIDs.push_back(tid);
	}

	return true;
}


std::string Contact::toString() const {

	std::string result = std::to_string(id) + " " +
		name + " " +
		gender + " " +
		age + " " +
		phone + " " +
		city + " " +
		company + " " +
		address;

	for (int tid : tagIDs) {
		result += " " + globalIdToTag[tid];
	}

	return result;
}

std::string Contact::getShortInfo() const {
	return std::to_string(id) + ". " + name;
}

std::vector<std::string> Contact::getTagStrings() const {
	std::vector<std::string> names;
	for (int tid : tagIDs) {
		names.push_back(globalIdToTag[tid]);
	}
	return names;
}