cmake_minimum_required(VERSION 3.20)
project(STM_ELN)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Find the libraries
find_package(fmt CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(implot CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(ftxui CONFIG REQUIRED)

# 2. Define the executable
# Note: I'm using src/main.cpp
add_executable(STM_ELN src/main.cpp src/Experiment.cpp src/Experiment.h src/Experiment_IO.cpp src/Experiment_IO.h src/TerminalUI.h src/TerminalUI.cpp "src/Utilities.cpp" "src/Utilities.h")

# 3. Link libraries
target_link_libraries(STM_ELN PRIVATE
    ftxui::component 
    ftxui::dom 
    ftxui::screen
    nlohmann_json::nlohmann_json
    fmt::fmt
    imgui::imgui
    implot::implot
    glfw        # Changed from glfw3 to glfw (standard vcpkg target name)
    OpenGL::GL
)

# 4. Set working directory so it can find your data files
set_target_properties(STM_ELN PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")