cmake_minimum_required(VERSION 3.24)
project(Project_Final)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project_Final cmake-build-debug/main.cpp
        cmake-build-debug/pcCombo.h
        cmake-build-debug/pcUtilities.h
        cmake-build-debug/pcUtilities.cpp
        cmake-build-debug/dist/json/json.h
        cmake-build-debug/dist/json/json-forwards.h
        cmake-build-debug/dist/jsoncpp.cpp
        )
