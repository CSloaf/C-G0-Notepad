#define FMT_HEADER_ONLY
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/string.hpp>

#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/event.hpp"
#include "Experiment.h"
#include "Experiment_IO.h"

#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <filesystem>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <fmt/core.h>
#include "TerminalUI.h"

#include "Utilities.h"

using namespace ftxui;
namespace fs = std::filesystem;

std::vector<std::string> expNames(const fs::path& directory) {
	std::vector<std::string> names;

	if (!fs::exists(directory) || !fs::is_directory(directory)) {
		return names;
	}

	for (const auto& dir_entry : fs::directory_iterator(directory)) {
		if (dir_entry.is_regular_file() && dir_entry.path().extension() == ".json") {
			names.push_back(dir_entry.path().stem().string());
		}
	}
	return names;
}

ButtonOption ButtonStyle() {
	auto option = ButtonOption::Animated();
	option.transform = [](const EntryState& s) {
		auto element = text(s.label);
		if (s.focused) {
			element |= bold;
		}
		return element | center | borderEmpty | flex;
		};
	return option;
}

ButtonOption ModernStyle() {
	auto option = ButtonOption::Animated();
	option.transform = [](const EntryState& s) {
		auto element = text(s.label) | center;
		if (s.focused) {
			return element | bgcolor(Color::White) | color(Color::Black) | bold | border;
		}
		else {
			return element | bold | border; // | bgcolor(Color::GrayDark) | color(Color::White);
		}
		};
	return option;
}

std::string getDate() {
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);
	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d");
	return ss.str();
}

int MenuTerminalUI() {
	auto screen = ScreenInteractive::Fullscreen(); // TerminalOutput();

	std::vector<std::string> entries = {
		"New File",
		"Load Existing File",
		"Exit",
	};
	int selected = 0;

	MenuOption option;
	option.on_enter = screen.ExitLoopClosure();
	auto menu = Menu(&entries, &selected, option);

	// Got Gemini Pro to assist with this logo bit so you don't have my ASCII art version of it :)
	auto logo_renderer = Renderer([&] {
		return vbox({
			text(R"(  ██████╗       ██████╗  ██████╗ )") | bold | color(Color::Cyan),
			text(R"( ██╔════╝██████╗██╔════╝ ██╔═████╗)") | bold | color(Color::Cyan),
			text(R"( ██║     ╚═════╝██║  ███╗██║██╔██║)") | bold | color(Color::Cyan),
			text(R"( ██║            ██║   ██║████╔╝██║)") | bold | color(Color::Cyan),
			text(R"( ╚██████╗       ╚██████╔╝╚██████╔╝)") | bold | color(Color::Cyan),
			text(R"(  ╚═════╝        ╚═════╝  ╚═════╝ )") | bold | color(Color::Cyan),
			text(" "), // Spacer
			text("N O T E P A D   ") | bold,
			}) | center;
		});


	auto main_renderer = Renderer(menu, [&] {
		return vbox({
			// Top: The Logo
			logo_renderer->Render(),

			text(" "),
			separator(),
			text(" "), // Spacer

			// Bottom: The Menu
			vbox({
				menu->Render() | border | center
			})
			}) | center | border; // Center everything on screen
		});


	//auto styled_menu = Renderer(menu, [&] {
	//	return menu->Render()
	//		| bgcolor(Color::RGB(28, 28, 28))
	//		| color(Color::White);
	//	});

	auto handler = CatchEvent(main_renderer, [&](Event event) {
		if (event == Event::Escape) {
			selected = 2;
			screen.Exit();
			return true;
		}
		return false;
		});

	screen.Loop(handler); //menu

	return selected;
}

std::string LoadTerminalUI(const fs::path& folder) {
	auto screen = ScreenInteractive::Fullscreen();  //TerminalOutput();
	std::vector<std::string> files = expNames(folder);
	int selected = 0;
	bool cancelled = false;

	// Generating the details for the search bar
	std::string query = "";
	std::vector<std::string> display_names;
	std::vector<std::string> actual_filenames;
	auto refresh_list = [&]() {
		auto results = Search(folder, query);
		display_names.clear();
		actual_filenames.clear();

		for (const auto& res : results) {
			// e.g. "2023-10-26 | Pyridine Test"
			display_names.push_back(res.date + " | " + res.title);
			actual_filenames.push_back(res.filename);
		}

		// Prevent crashes if the list shrinks and 'selected' is now out of bounds
		if (selected >= display_names.size()) {
			selected = display_names.empty() ? 0 : display_names.size() - 1;
		}
		};

	refresh_list();

	if (files.empty()) return "";

	InputOption search_options;
	search_options.on_change = refresh_list;
	Component search_bar = Input(&query, "", search_options);

	auto menu = Menu(&display_names, &selected); // , MenuOption::Toggle());

	auto load_button = Button("LOAD", screen.ExitLoopClosure(), ModernStyle()); //ButtonOption::Animated()); //ButtonStyle());

	auto cancel_button = Button("CANCEL", [&] {
		cancelled = true;
		screen.Exit();
		}, ModernStyle()); // ButtonOption::Animated());

	auto layout = Container::Vertical({ search_bar , Container::Horizontal({ Container::Vertical({ load_button, cancel_button }), menu }) });

	auto renderer = Renderer(layout, [&] {
		return
			vbox({
			//search_bar->Render() | bold | border,
			//hbox({ text(" FILTER: ") | bold, search_bar->Render() | bold }),
			//separator(),
			hbox({
				vbox({

				hbox({ text(" FILTER: ") | bold, search_bar->Render() | bold }) | size(WIDTH, EQUAL, 75),
				separator(),
				//vbox({
				//	hbox({ text(" FILTER: ") | bold, search_bar->Render() | bold }),
				//	separator(),
				//	}),
				hbox({
				vbox({
					text(" OPTIONS ") | center | bold,
						separator(),
						vbox({load_button->Render()}), // | border,
						text(""),
						vbox({cancel_button->Render()}), // | border,
					}) | size(WIDTH, EQUAL, 15) | border, // | bgcolor(Color::RGB(18, 18, 18))

				vbox({
					text(" SELECT EXPERIMENT LOG ") | center | bold,
					separator(),
					menu->Render() | vscroll_indicator | frame | flex
					}) | border | flex

				}) | center
				}) | center
					}) | border | center | flex,
				});
		});

	auto handler = CatchEvent(renderer, [&](Event event) {
		if (event == Event::Escape) {
			cancelled = true; // Mark as cancelled so we return ""
			screen.Exit();
			return true;
		}
		return false;
		});

	screen.Loop(handler); //use renderer for no escape 

	if (cancelled || actual_filenames.empty()) {
		return "";
	}
	else {
		return actual_filenames[selected]; //files[selected] + ".json";
	}

}

void RunTerminalUI(Experiment& exp, const std::filesystem::path& folder, std::string filename = "") {

	if (!filename.empty()) {
		load_exp(exp, folder / filename);
	}
	else {
		exp.date = getDate();
	}

	auto screen = ScreenInteractive::Fullscreen(); //TerminalOutput();  //Fullscreen();  //TerminalOutput();
	screen.TrackMouse(false);

	Component title = Input(&exp.title, "Experiment Title");
	Component eln_id = Input(&exp.eln_id, "ELN ID");
	Component date = Input(&exp.date, "Date");
	Component smiles = Input(&exp.smiles, "SMILES String");
	Component instrument = Input(&exp.instrument, "Instrument Name (e.g. Leviathan)");
	Component conditions = Input(&exp.conditions, "Experiment conditions (e.g. Bias: 200mV, Rate: 10 nm/s, etc...)");
	Component data_folder = Input(&exp.data_folder, "Save Data Folder Name (e.g. /usr/BIPY-200mV...)");
	Component notes = Input(&exp.notes, "Free Text Notes...");

	std::string error_msg;
	// TODO Sort out all the return cases. Its like 2017 Twin Peaks in here...
	Component save_button = Button("   SAVE & EXIT   ", [&] {
		if (exp.title.empty()) {
			error_msg = " | You must include a log title to save.| ";
			return;
		}

		fs::path save_path;
		fs::path new_path = folder / (exp.title + ".json");

		if (filename.empty()) {
			if (fs::exists(new_path)) {
				error_msg += " | Log title already exists, please choose another name | ";
				return;
			}
			save_path = new_path;
		}
		else {
			fs::path old_path = folder / filename;
			if (old_path != new_path) {
				if (fs::exists(new_path)) {
					error_msg += " | I can't remember what this error does! | ";
					return;
				}
				fs::rename(old_path, new_path);
			}
			save_path = new_path;
		}
		save_exp(exp, save_path);
		screen.Exit();
		}, ButtonOption::Animated());

	auto container = Container::Vertical({
		title,
		eln_id,
		date,
		smiles,
		instrument,
		conditions,
		data_folder,
		notes,
		save_button
		});

	auto component_renderer = Renderer(container, [&] {
		return vbox({
			text(" EXPERIMENT LOG ENTRY ") | border,
			hbox(text(" TITLE:  "), title->Render()),
			hbox(text(" ELN ID: "), eln_id->Render()),
			hbox(text(" DATE:   "), date->Render()),
			text(""),
			hbox(text(" SMILES STRING:         "), smiles->Render()),
			hbox(text(" INSTRUMENT NAME:       "), instrument->Render()),
			hbox(text(" EXPERIMENT CONDITIONS: "), conditions->Render()),
			//separator(),
			hbox(text(" SAVE DATA FOLDER NAME: "), data_folder->Render()),
			//separator(),
			text(""),
			hbox(text(" NOTES: "), notes->Render()) | border, // | flex,
			//separator(),

			text(error_msg) | color(Color::Red) | center,

			save_button->Render() | border | center
			})
			| bgcolor(Color::RGB(18, 18, 18)) | color(Color::White) | border;
		});

	auto event_handler = CatchEvent(component_renderer, [&](Event event) {
		if (event == Event::Escape) {
			screen.Exit();
			return true;
		}
		return false;
		});

	screen.Loop(event_handler);

}

void loopUI(const fs::path folder) {
	while (true) {
		int state = MenuTerminalUI();

		Experiment exp;

		if (state == 0) {
			exp = Experiment();
			RunTerminalUI(exp, folder, "");
		}
		else if (state == 1) {
			std::string file = LoadTerminalUI(folder);
			if (!file.empty()) {
				RunTerminalUI(exp, folder, file);
			}
		}
		else if (state == 2) {
			break;
		}
		else {
			fmt::print("What did you do to break me?!?\n");
			break;
		}
	}
}