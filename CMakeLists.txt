cmake_minimum_required(VERSION 3.7)
project(GamMacs)

find_package(SDL2 REQUIRED)
include_directories(gamacs ${SDL2_INCLUDE_DIRS})

add_executable(gamacs src/main.cpp src/Env.cpp src/Player.cpp)
target_link_libraries(gamacs ${SDL2_LIBRARIES})
