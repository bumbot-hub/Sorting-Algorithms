cmake_minimum_required(VERSION 4.1)
project(AiZO)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(AiZO
        src/Experiment.cpp
        include/ArrayGenerator.hpp
        include/SortingAlgorithm.hpp
        include/Timer.hpp
        include/Experiment.hpp
)

target_include_directories(AiZO PRIVATE include)