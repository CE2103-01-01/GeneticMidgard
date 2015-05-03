cmake_minimum_required(VERSION 3.1)
project(ProjectMidgardLogic)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")

set(HEADER_FILES Interface/Random.h
                 Constants.h
                 Models/Population.h
                 Models/Subject.h
                 Models/Chromosome.h
                 Models/Terrain.h
                 Models/movilObjectManager.h
                 Algorithms/lifeLaboratory.h
                 Algorithms/ChromosomeMixer.h
                 Algorithms/lifeLaboratory.h
                 Algorithms/GeneralFitnessCalculator.h
                 Algorithms/BinaryReader.h
                 Generators/EvolutionGenerator.h
                 Proof/chromosomeMixerProof.h
                 Proof/proofBinary.h
                 Data/BitVector.h
                 Data/DoubleList.h
                 Data/PriorityQueue.h
                 Data/PThreadParam.h
                 Data/Leaf.h
                 Data/Tree.h
                 Data/TreeProof.h
                 )

set(SOURCE_FILES main.cpp
                 Interface/Random.cpp
                 Constants.cpp
                 Models/Population.cpp
                 Models/Subject.cpp
                 Models/Chromosome.cpp
                 Models/Terrain.cpp
                 Models/movilObjectManager.cpp
                 Generators/EvolutionGenerator.cpp
                 Algorithms/ChromosomeMixer.cpp
                 Algorithms/lifeLaboratory.cpp
                 Algorithms/GeneralFitnessCalculator.cpp
                 Algorithms/BinaryReader.cpp
                 Proof/chromosomeMixerProof.cpp
                 Proof/proofBinary.cpp
                 )

set (DATA_STRUCTS   Data/BitVector.cpp
                    Data/TreeProof.cpp
                    Data/Leaf.cpp
                    Data/PThreadParam.cpp)
                    
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


file(GLOB RES_FILES res/constant.xml
                    res/genes.xml)

file(COPY ${RES_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_package (Threads)

add_executable(ProjectMidgardLogic  ${SOURCE_FILES}
                                    ${HEADER_FILES}
                                    ${TMX_FILES}
                                    ${XML}
                                    ${DATA_STRUCTS}
                                    ${RES_FILES} Proof/laboratoryProof.h Proof/laboratoryProof.cpp)

target_link_libraries (ProjectMidgardLogic ${CMAKE_THREAD_LIBS_INIT})

add_subdirectory(GUI)