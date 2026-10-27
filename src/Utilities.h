#pragma once

#include <vector>
#include <filesystem>
#include <string>

struct SearchResult {
	std::string filename;
	std::string date;
	std::string title;
};

std::vector<SearchResult> Search(const std::filesystem::path& folder, const std::string query);