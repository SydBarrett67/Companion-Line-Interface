cmake_minimum_required(VERSION 3.20)

project(pet VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pet
    src/main.cpp
    src/Pet.cpp
    src/ConfigParser.cpp
    src/Vars.cpp
    src/CLI.cpp
    src/Logger.cpp
)

target_include_directories(pet PRIVATE include)

