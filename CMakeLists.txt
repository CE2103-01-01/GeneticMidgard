cmake_minimum_required(VERSION 3.1)
project(ProjectMidgard)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")

execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/res
                                                           ${CMAKE_BINARY_DIR}/res)

set(HEADER_FILES Interface/Random.h
                 Constants.h
                 #Models/Population.h
                 Models/Subject.h
                 Models/Chromosome.h
                 Models/Weapon.h
                 Models/Armor.h
                 Algorithms/Algorithms.h
                 Algorithms/ChromosomeMixer.h
                 Generators/EvolutionGenerator.h
                 Data/Leaf.h
                 Data/Tree.h
                 Data/TreeProof.h
  )

set(SOURCE_FILES main.cpp
                 Interface/Random.cpp
                 Constants.cpp
                 #Models/Population.cpp
                 Models/Subject.cpp
                 Models/Chromosome.cpp
                 Models/Weapon.cpp
                 Models/Armor.cpp
                 Models/Terrain.cpp
                 Generators/EvolutionGenerator.cpp
                 Algorithms/Algorithms.cpp
                 Algorithms/ChromosomeMixer.cpp)

set (DATA_STRUCTS   Data/TreeProof.cpp
                    Data/DoubleList.cpp
                    Data/Leaf.cpp)
                    
set(TMX_FILES   libs/TMXParser.cpp
                libs/base64.cpp
                libs/TMXParser.h
                libs/base64.h)
                
set(XML libs/rapidxml/rapidxml.hpp
        libs/rapidxml/rapidxml_iterators.hpp
        libs/rapidxml/rapidxml_print.hpp
        libs/rapidxml/rapidxml_utils.hpp
        libs/pugixml/pugiconfig.hpp
        libs/pugixml/pugixml.hpp
        libs/pugixml/pugixml.cpp)

add_executable(ProjectMidgard   ${SOURCE_FILES}
                                ${HEADER_FILES}
                                ${TMX_FILES}
                                ${XML}
                                ${DATA_STRUCTS})