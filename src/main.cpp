#define FMT_HEADER_ONLY
#include <fmt/core.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Experiment.h"
#include "Experiment_IO.h"
#include "TerminalUI.h"
#include <string>

int main() {
	std::filesystem::path folder = "./Experiments";

	if (!std::filesystem::exists(folder)) {
		std::filesystem::create_directory(folder);
	}

	loopUI(folder);

	return 0;
}
