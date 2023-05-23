cmake_minimum_required(VERSION 3.21)
project(ahr)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(libs)

add_executable(ahr main.cpp
        Judgment.cpp Judgment.h
        PairwiseJudgment.cpp PairwiseJudgment.h
        Judgments.cpp
        EigenCalculator.cpp
        CommonObject.cpp
        CommonObject.h EigenCalculator.h
        Judgments.h User.cpp User.h
        Node.cpp Node.h
        Alternative.cpp Alternative.h
        Hierarchy.cpp Hierarchy.h
        Model.cpp Model.h
        Storage.cpp Storage.h
        IDGenerator.cpp IDGenerator.hpp)

target_link_libraries(ahr PUBLIC
        matrix)
target_link_libraries(ahr PUBLIC
        graphs)
