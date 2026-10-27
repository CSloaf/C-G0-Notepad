#define FMT_HEADER_ONLY
#include "Experiment_IO.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::ordered_json;

RWjson save_exp(const Experiment& exp, const std::filesystem::path& file) {

	std::ofstream o(file);
	if (!o.is_open()) {
		return { false, nullptr };
	}

	json data = exp;
	o << std::setw(4) << data << std::endl;

	return { true, data, exp };
}

RWjson load_exp(Experiment& exp, const std::filesystem::path& file) {

	std::ifstream f(file);
	if (!f.is_open()) {
		return { false, nullptr };
	}

	json data = json::parse(f);
	exp = data.get<Experiment>();

	return { true, data, exp };
}