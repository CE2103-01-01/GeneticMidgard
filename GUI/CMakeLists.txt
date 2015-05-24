project(ProjectMidgardGUI)
add_executable(ProjectMidgardGUI main.cpp Constants.h Map.cpp Map.h
                                ../Network/SocketGUI.cpp ../Network/SocketGUI.h Poblacion.cpp Poblacion.h Slider.cpp Slider.h ../Network/SocketConfig.h ../Data/Queue.h)

if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(ProjectMidgardGUI ${SFML_LIBRARIES})
endif()

configure_file(../res/mapa.tmx ../res/mapa.tmx COPYONLY)
configure_file(../res/terrain_atlas_small.png ../res/terrain_atlas_small.png COPYONLY)
configure_file(../res/roboto.ttf ../res/roboto.ttf COPYONLY)
