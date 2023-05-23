SET(HEADERS
        matrix.hpp)
SET(SOURCES
        matrix.cpp)

add_library(matrix
        ${HEADERS}
        ${SOURCES})

target_include_directories(matrix PUBLIC ./)