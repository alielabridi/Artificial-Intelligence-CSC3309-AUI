cmake_minimum_required(VERSION 3.6)
project(Asg2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Node.h PegsLogicNode.h SearchEngine.h ExploredSet.h)
add_executable(Asg2 ${SOURCE_FILES})