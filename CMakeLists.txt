cmake_minimum_required(VERSION 3.23)
project(Advent_of_Code_2022)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Helpers)
list(APPEND EXTRA_LIBS Helpers)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/Helpers")

add_executable(Day1 day1.cpp)
add_executable(Day2 day2.cpp)
add_executable(Day3 day3.cpp Helpers/helper.cpp)
add_executable(Day4 day4.cpp Helpers/helper.cpp)
add_executable(Day5 day5.cpp Helpers/helper.cpp)
add_executable(Day6 day6.cpp Helpers/helper.cpp)
add_executable(Main main.cpp)
