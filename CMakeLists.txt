cmake_minimum_required(VERSION 3.10)
project(BankingApp)

# Enable C++17 (or higher) since FTXUI requires it
set(CMAKE_CXX_STANDARD 20)

# Specify the path to FTXUI, if it's installed via a package manager
# Uncomment and modify the following if you're using vcpkg, for example
 set(CMAKE_TOOLCHAIN_FILE "C:/Tools/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Add FTXUI submodule if it's added as one
# add_subdirectory(ftxui)

# Find the FTXUI package (if installed via a package manager)
find_package(ftxui CONFIG REQUIRED)

# Include the main source code for your app
add_executable(BankingApp "Banking App Final Project/main.cpp")

# Link the FTXUI libraries to your app
target_link_libraries(BankingApp ftxui)

# Include the ftxui headers (if it's not in the subdirectory already)
# target_include_directories(BankingApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ftxui/include)