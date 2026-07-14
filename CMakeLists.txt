cmake_minimum_required(VERSION 3.20)

project(pet VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(pet_core STATIC
    src/Pet.cpp
    src/ConfigParser.cpp
    src/Vars.cpp
    src/CLI.cpp
    src/Logger.cpp
)

# Set include directories for the core library 
target_include_directories(pet_core PUBLIC include)

# Main exec
add_executable(pet src/main.cpp)
target_link_libraries(pet PRIVATE pet_core)


# Minigames compilation
file(GLOB MINIGAME_SOURCES CONFIGURE_DEPENDS "minigames/src/*.cpp")

foreach(SOURCE_FILE ${MINIGAME_SOURCES})
    get_filename_component(MINIGAME_NAME ${SOURCE_FILE} NAME_WE)
    
    add_executable(${MINIGAME_NAME} ${SOURCE_FILE})
    
    target_link_libraries(${MINIGAME_NAME} PRIVATE pet_core)
    
    set_target_properties(${MINIGAME_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/minigames"
    )    
endforeach()