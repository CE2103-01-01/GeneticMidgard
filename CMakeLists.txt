cmake_minimum_required(VERSION 3.1)
project(ProjectMidgard)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")

execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/res
                                                           ${CMAKE_BINARY_DIR}/res)

set(SOURCE_FILES main.cpp
                 Interface/Random.cpp
                 Interface/Random.h
                 Constants.cpp
                 Constants.h
                 Models/Subject.cpp
                 Models/Subject.h
                 Models/Genes.cpp
                 Models/Genes.h
                 Models/Weapon.cpp
                 Models/Weapon.h
                 Models/Armor.cpp
                 Models/Armor.h
                 Models/Terrain.cpp
                 Models/Terrain.h
                 Models/Population.cpp
                 Models/Population.h
                 Generators/EvolutionGenerator.cpp
                 Generators/EvolutionGenerator.h
                 Algorithms/Algorithms.cpp
                 Algorithms/Algorithms.h
                 )
set (DATA_STRUCTS
                    Data/DoubleList.cpp
                    Data/DoubleList.h
                    Data/Tree.h
                    Data/Leaf.cpp
                    Data/Tree.h)
set(TMX_FILES libs/TMXParser.h
                libs/TMXParser.cpp
                libs/base64.cpp
                libs/base64.h)
set(XML libs/rapidxml/rapidxml.hpp
        libs/rapidxml/rapidxml_iterators.hpp
        libs/rapidxml/rapidxml_print.hpp
        libs/rapidxml/rapidxml_utils.hpp
        libs/pugixml/pugixml.cpp
        libs/pugixml/pugiconfig.hpp
        libs/pugixml/pugixml.hpp
        )


add_executable(ProjectMidgard ${SOURCE_FILES} ${TMX_FILES} ${XML} ${DATA_STRUCTS}  )