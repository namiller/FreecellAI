cmake_minimum_required(VERSION 2.8)
add_definitions(-std=c++11)
add_library(game GameState.cpp ASCIIviz.cpp Card.cpp Move.cpp)
