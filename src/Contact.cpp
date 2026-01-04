#include "Contact.h"
#include <iostream>
#include <sstream>
#include <algorithm>

bool Contact::parseFromString(const std::string& line) {
	std::stringstream ss(line);
	std::string segment;
	std::vector<std::string> parts;

	while (ss >> segment) {
		parts.push_back(segment);
	}

	if (parts.size() < 7) {
		std::cerr << "错误: 数据格式不足7项 -> " << line << std::endl;
		return false;
	}

	try {
		std::stoi(parts[0]);
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

	tags.clear();
	for (size_t i = 7; i < parts.size(); i++) {
		tags.push_back(parts[i]);
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
		company;

	for (const auto& tag : tags) {
		result += " " + tag;
	}

	return result;
}

std::string Contact::getShortInfo() const {
	return std::to_string(id) + ". " + name;
}