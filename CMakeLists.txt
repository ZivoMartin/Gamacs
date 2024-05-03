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
    Lablib/lib/button.c
    Lablib/lib/lablib.c
    Lablib/lib/cursor.c
    Lablib/lib/scene.c
    Lablib/lib/input.c
)

include_directories(${SDL2_ALL_INC})
    
set(SOURCES
    src/main.cpp
    src/Env.cpp
    
    src/sprites/Sprite.cpp
    src/sprites/Static.cpp
    src/sprites/Movable.cpp

    src/game/MainGame.cpp  
    
    src/game/game_characters/MapEntity.cpp
    src/game/game_characters/GamePlayer.cpp
    src/game/game_characters/Pnj.cpp
    src/game/game_characters/monsters/Monster.cpp
    src/game/game_characters/monsters/Orc.cpp

    src/Position.cpp
    src/game/Map.cpp
    src/game/TxtBubble.cpp
    
    src/main_menu/MainMenu.cpp
    
    src/battle/MainBattle.cpp
    src/battle/Pown.cpp
    src/battle/PownMovable.cpp
    src/battle/PownMonster.cpp
    src/battle/PownPlayer.cpp
        
    src/interfaces/Player.cpp
    src/interfaces/Renderer.cpp
    src/interfaces/MovableFighter.cpp
    
    src/entity_settings/Setting.cpp
    src/entity_settings/SettingFighter.cpp
)

# Add an executable with the above sources
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(gamacs ${SDL2_ALL_LIBS} lablib)


file(COPY res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
