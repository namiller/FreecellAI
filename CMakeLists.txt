cmake_minimum_required (VERSION 2.8)
project (FreecelllAI)

include_directories(src/game_logic src/solver)

add_definitions(-std=c++11)
add_definitions(-g)
add_subdirectory(src)
add_subdirectory(test)
add_executable(FreecellAI game.cpp)
add_executable(test1 test/test1.cpp)
target_link_libraries(FreecellAI game solver)
target_link_libraries(test1 game)
