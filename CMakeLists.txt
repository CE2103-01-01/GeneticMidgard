cmake_minimum_required(VERSION 3.1)
project(ProjectMidgard)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")

set(SOURCE_FILES main.cpp)
add_executable(ProjectMidgard ${SOURCE_FILES} Interface/Random.cpp Interface/Random.h Constants.cpp Constants.h Models/Subject.cpp Models/Subject.h Models/Genes.cpp Models/Genes.h Models/Weapon.cpp Models/Weapon.h Models/Armor.cpp Models/Armor.h Generators/EvolutionGenerator.cpp Generators/EvolutionGenerator.h Algorithms/Algorithms.cpp Algorithms/Algorithms.h)