#pragma once
#include "Experiment.h"
#include <filesystem>

RWjson save_exp(const Experiment& exp, const std::filesystem::path& file);

RWjson load_exp(Experiment& exp, const std::filesystem::path& file);