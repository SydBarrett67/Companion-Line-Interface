cmake_minimum_required(VERSION 3.20)

# Dichiarazione del progetto e standard C++
project(pet VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Raccolta di tutti i file sorgente (.cpp) e header (.h)
file(GLOB_RECURSE SRC_FILES src/*.cpp include/*.h)

# Genera l'eseguibile a partire dai sorgenti
add_executable(pet ${SRC_FILES})

# Inclusione delle cartelle degli header
target_include_directories(pet PRIVATE include)

