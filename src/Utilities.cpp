#define FMT_HEADER_ONLY
#include "Utilities.h"
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>

using json = nlohmann::ordered_json;

namespace fs = std::filesystem;

std::vector<SearchResult> Search(const fs::path& folder, const std::string query) {
	std::vector<SearchResult> results;

	std::string query_lcase = query;
	std::transform(query_lcase.begin(), query_lcase.end(), query_lcase.begin(), ::tolower);

	std::vector<std::string> keywords;
	std::stringstream ss(query_lcase);
	std::string word;
	while (ss >> word) {
		keywords.push_back(word);
	}

	for (const auto& entry : fs::directory_iterator(folder)) {
		if (entry.path().extension() == ".json") {
			try {
				std::fstream f(entry.path());
				json data = json::parse(f);

				std::string title = data.value("title", "");
				std::string instrument = data.value("instrument", "");
				std::string smiles = data.value("smiles", "");
				std::string eln_id = data.value("eln_id", "");
				std::string conditions = data.value("conditions", "");

				std::string full_list = title + " " + instrument + " " + smiles + " " + eln_id + " " + conditions;
				std::transform(full_list.begin(), full_list.end(), full_list.begin(), ::tolower);

				bool matches_all = true;
				for (const auto& kw : keywords) {
					if (full_list.find(kw) == std::string::npos) {
						matches_all = false; // skip file if not resent
						break;
					}
				}

				// If it contains all keywords then add to results
				if (matches_all) {
					results.push_back({
						entry.path().filename().string(),
						data.value("date", "Unknown Date"),
						title
						});
				}
			}
			catch (...) {
				continue;
			}
		}
	}

	// Sort the final results by date rather than name
	std::sort(results.begin(), results.end(), [](const SearchResult& a, const SearchResult& b) {
		return a.date > b.date;
		});
	return results;
}