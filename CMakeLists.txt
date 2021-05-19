cmake_minimum_required(VERSION 2.8)

project(chaos)


file(GLOB program_src
     "*.h"
     "*.cpp"
)

SET(CMAKE_BUILD_TYPE Debug)
add_executable(${PROJECT_NAME} ${program_src})
