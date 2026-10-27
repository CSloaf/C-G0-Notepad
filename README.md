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