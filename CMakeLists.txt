cmake_minimum_required(VERSION 3.24)
project(Project_Final)

set(CMAKE_CXX_STANDARD 14)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)

find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

add_executable(Project_Final cmake-build-debug/main.cpp
        cmake-build-debug/PCCombo.h
        cmake-build-debug/PCUtilities.h
        cmake-build-debug/PCUtilities.cpp
        cmake-build-debug/dist/json/json.h
        cmake-build-debug/dist/json/json-forwards.h
        cmake-build-debug/dist/jsoncpp.cpp
        cmake-build-debug/Mergesort.h cmake-build-debug/Quicksort.h
        cmake-build-debug/SFMLtools.h
)
target_link_libraries(Project_Final sfml-system sfml-window sfml-graphics sfml-audio)
include_directories(c:/SFML/include/SFML)
