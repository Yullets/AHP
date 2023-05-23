set(SOURCES
        graph.cpp)
set(HEADERS
        graph.hpp)


add_library(graphs
        ${SOURCES}
        ${HEADERS})

target_include_directories(graphs PUBLIC ./)

target_link_libraries(graphs PUBLIC matrix)