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
                 Data/BitVector.h
                 Data/DoubleList.h
                 Data/PriorityQueue.h
                 Data/PThreadParam.h
                 Data/Leaf.h
                 Data/Tree.h
                 Data/TreeProof.h
                 Network/SocketLogic.h
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
                 Network/SocketLogic.cpp
                 )

set (DATA_STRUCTS   Data/BitVector.cpp
                    Data/TreeProof.cpp
                    Data/Leaf.cpp
                    Data/PThreadParam.cpp)



set(XML
        libs/pugixml/pugixml.cpp)


#Adding Resources

configure_file( res/constant.xml res/constant.xml COPYONLY)
configure_file(res/genes.xml res/genes.xml COPYONLY)





find_package (Threads)

add_executable(ProjectMidgardLogic  ${SOURCE_FILES}
                                    ${HEADER_FILES}
                                    ${XML}
                                    ${DATA_STRUCTS}
                                    ${RES_FILES} Models/PopulationManager.cpp Models/PopulationManager.h Models/AgeManager.cpp Models/AgeManager.h Network/SocketConfig.h Data/Queue.h Models/God.cpp Models/God.h)
include_directories(../libs)
target_link_libraries (ProjectMidgardLogic ${CMAKE_THREAD_LIBS_INIT})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML REQUIRED system window graphics network)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(ProjectMidgardLogic ${SFML_LIBRARIES})
endif()

add_subdirectory(GUI)