# C-G0 Notepad

## About
**A Retro-Terminal Lab Book**  
C-G0 Notepad is a simple and lightweight scientific scratchpad.
It supports rapid logging compared to large ELNs and is designed to act as an aid during measurements or computational projects. In short, it is a 'smart', tailored, notepad for experimental and computational work.
It was originally designed for molecular electronics but is useful in nanoscience in general. It may also be useful for other scientific fields, particularly those that require rapid logging of experimental data or computational results.
It is designed to be used in a terminal environment, with a focus on speed and minimalism.

## Features
* **Rapid Logging:** Designed to run locally or on network attached storage systems for logging experiment/computational results. Optionally right next to the experimental data itself.
* **Compatible with ELNs:** Can be used as a standalone notepad or in conjunction with an ELN. It can also be used to log data that is later uploaded/backed-up to an ELN.
* **Filtering Feature:** Filters past logs by Title, Instrument, Exp Conditions, SMILES string, or ELN ID.
* **Session Grouping:** Automatically sorts logs chronologically so the most recent measurements are always at the top.
* **Data Sovereignty:** Saves everything as clean, human-readable `.json` files. No proprietary databases or formats.

## Technical Details
* **Language:** C++20
* **libraries:** FTXUI (TUI framework), nlohmann/json (JSON Parsing), fmt (some debug string formatting)

## How to Cite

If you use C-G0 Notepad or its code in your research or educational materials, please cite as follows:

> J. M. F. Morris (2026). C-G0 Notepad: A Retro-Terminal Lab Book (Version 1.0.0). Zenodo. https://doi.org/10.5281/zenodo.

## License

Copyright (C) 2026 James M. F. Morris.

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.


## Installation (Recommended for Windows Users)
If you simply want to run the C-G0 Notepad without compiling code, you can download the latest pre-compiled executable.

1. Navigate to the **[Releases](https://github.com/CSloaf/C-G0-Notepad/releases)** page on GitHub.
2. Download the latest `C-G0_Notepad_v1.0_Win64.zip_.zip`.
3. Extract the folder and double-click the `C-G0 Notepad.exe` to run the application.

The 'Experiments' folder contains your .json experiment files which contains the metadata and notes for each experiment. You can also create your own .json files and place them in this folder.  
The 'data' folder is empty upon download but it can be useful practice to store raw datasets here, keeping your data organised and in proximity to the experiments.

---

## Building from Source (For Developers)

This project uses modern C++20 and CMake. Dependencies are managed via `vcpkg` in manifest mode.

### Prerequisites
* A C++20 compatible compiler (MSVC, GCC, or Clang)
* [CMake](https://cmake.org/) (version 3.20 or higher)
* [vcpkg](https://vcpkg.io/) installed and bootstrapped

### Build Instructions
The easiest way to build the application is via the command line using standard CMake commands. 

1. Clone this repository to your local machine:
   ```bash
   git clone https://github.com/CSloaf/C-G0-Notepad.git
   ```
2. Navigate to the project directory:
   ```bash
   cd C-G0-Notepad
   ```
3. Configure the project with CMake, specifying the vcpkg toolchain file (make sure to replace `/path/to/vcpkg` with the actual path where vcpkg is installed on your machine):
   ```bash
   cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
   ```
4. Build the project:
   ```bash
   cmake --build build --config Release
   ```