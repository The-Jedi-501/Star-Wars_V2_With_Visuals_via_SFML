cmake_minimum_required(VERSION 3.16)
project(SW_V2)

set(CMAKE_CXX_STANDARD 17)

# find SFML and GDAL
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Audio)
find_package(GDAL REQUIRED)

# all your source files
add_executable(SW_V2
    src/SW_V2.cpp
)

target_include_directories(SW_V2 PRIVATE src)

# link the libraries
target_link_libraries(SW_V2
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
    GDAL::GDAL
)