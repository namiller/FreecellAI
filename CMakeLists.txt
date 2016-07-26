cmake_minimum_required (VERSION 2.8)
project (FreecelllAI)

add_definitions(-std=c++11)
add_subdirectory(src)
add_executable(FreecellAI game.cpp)
target_link_libraries(FreecellAI game)

