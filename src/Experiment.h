#pragma once
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::ordered_json;

// Experiment structure for passing to json
struct Experiment {
	std::string title;
	std::string eln_id;
	std::string date;
	std::string smiles;
	std::string instrument;
	std::string conditions;
	std::string data_folder;
	std::string notes;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Experiment, title, eln_id, date, smiles, instrument, conditions, data_folder, notes)
};

// RWjson data type for functions with bool and json data tpes
struct RWjson {
	bool returnVal;
	json _json;
	Experiment exp;
};