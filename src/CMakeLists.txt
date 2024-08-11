cmake_minimum_required(VERSION 3.25)
project(L_SHADE_DWSNs_CPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

include_directories(.)

add_executable(L_SHADE_DWSNs_CPP
        src/DE.h
        src/individual.cpp
        src/main.cpp
        src/myVector.h
        src/problem.h
        src/sensor.cpp
        src/target.cpp
        src/units.h
        src/utils.h src/problem.cpp src/DE.cpp)
