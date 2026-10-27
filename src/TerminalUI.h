#pragma once
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/string.hpp>
#include <filesystem>
#include "Experiment.h"

std::vector<std::string> expNames(const std::filesystem::path& directory);

int MenuTerminalUI();

std::string LoadTerminalUI(const std::filesystem::path& folder);

void RunTerminalUI(Experiment& exp, const std::filesystem::path& folder, std::string filename);

void loopUI(const std::filesystem::path folder = "./Experiments");

