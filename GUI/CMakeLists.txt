project(ProjectMidgardGUI)
add_executable(ProjectMidgardGUI main.cpp Constants.h Map.cpp Map.h
                                ../Network/SocketGUI.cpp ../Network/SocketGUI.h)

if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(ProjectMidgardGUI ${SFML_LIBRARIES})
endif()

execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/res
                                                           ${CMAKE_BINARY_DIR}/res)