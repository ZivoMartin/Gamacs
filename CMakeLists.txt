cmake_minimum_required(VERSION 3.7)
project(gamacs)


find_package(SDL2 REQUIRED)

find_path(SDL2_INCLUDE_DIR 
  NAMES SDL.h
  PATH_SUFFIXES SDL2 include/SDL2 include
  # NO_DEFAULT_PATH
  # PATHS ${SDL2_PATH}
  DOC "Where the SDL2 headers can be found"
  REQUIRED
  )

find_library(SDL2_LIBRARY
  NAMES SDL2
  PATH_SUFFIXES lib
  # NO_DEFAULT_PATH
  # PATHS ${SDL2_PATH}
  DOC "Where the SDL2 Library can be found"
  REQUIRED
)

find_library(SDL2_IMAGE_LIBRARY
  NAMES SDL2_image
  PATH_SUFFIXES lib
  # NO_DEFAULT_PATH
  # PATHS ${SDL2_PATH}
  DOC "Where the SDL2 Image Library can be found"
  REQUIRED
)

find_library(SDL2_TTF_LIBRARY
  NAMES SDL2_ttf
  PATH_SUFFIXES lib
  # NO_DEFAULT_PATH
  # PATHS ${SDL2_PATH}
  DOC "Where the SDL2 TTF Library can be found"
  REQUIRED
)

### use this variables in your CMakeLists.txt
set(SDL2_ALL_INC ${SDL2_INCLUDE_DIR})
set(SDL2_ALL_LIBS ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY})


set(CMAKE_C_FLAGS "-std=c99 -g -Wall")



add_library(lablib
    /home/martin/Travail/Gamacs/Lablib/lib/button.c
    /home/martin/Travail/Gamacs/Lablib/lib/lablib.c
    /home/martin/Travail/Gamacs/Lablib/lib/cursor.c
    /home/martin/Travail/Gamacs/Lablib/lib/scene.c
    /home/martin/Travail/Gamacs/Lablib/lib/input.c
)

include_directories(${SDL2_ALL_INC})
    
set(SOURCES
    src/main.cpp
    src/Env.cpp
    src/Sprite.cpp
    src/movables/Player.cpp 
    src/movables/Movable.cpp
    src/movables/monsters/Monster.cpp
    src/movables/monsters/Orc.cpp
    src/RegularAction.cpp
    src/view/Map.cpp
)

# Add an executable with the above sources
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(gamacs ${SDL2_ALL_LIBS} lablib)


file(COPY res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
