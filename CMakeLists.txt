cmake_minimum_required(VERSION 3.28)
project(Kursovaya)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Kursovaya
        main.cpp
        Header.h
        NetermAnalyze.cpp
        samples.txt
        NetermPerform.cpp
)
