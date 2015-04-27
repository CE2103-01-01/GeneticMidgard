cmake_minimum_required(VERSION 3.1)
project(ProjectMidgard)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")

execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/res
                                                           ${CMAKE_BINARY_DIR}/res)

set(HEADER_FILES                 Interface/Random.h
                                 Constants.h
                                 Models/Subject.h
                                 Models/Genes.h
                                 Models/Weapon.h
                                 Algorithms/Algorithms.h
                                 Models/Armor.h
                                 Generators/EvolutionGenerator.h
                                 Data/Leaf.h
                                 Data/Tree.h
                                 Data/TreeProof.h)

set(SOURCE_FILES main.cpp
                 Interface/Random.cpp
                 Constants.cpp
                 Models/Subject.cpp
                 Models/Genes.cpp
                 Models/Weapon.cpp
                 Models/Armor.cpp
                 Data/Leaf.cpp
                 Data/TreeProof.cpp
                 Generators/EvolutionGenerator.cpp
                 Algorithms/Algorithms.cpp)

set(TMX_FILES libs/TMXParser.h
                libs/TMXParser.cpp)

set(XML libs/rapidxml/rapidxml.hpp
        libs/rapidxml/rapidxml_iterators.hpp
        libs/rapidxml/rapidxml_print.hpp
        libs/rapidxml/rapidxml_utils.hpp
        libs/pugixml/pugixml.cpp
        libs/pugixml/pugiconfig.hpp
        libs/pugixml/pugixml.hpp)


add_executable(ProjectMidgard ${SOURCE_FILES} ${TMX_FILES} ${XML} libs/base64.cpp libs/base64.h)