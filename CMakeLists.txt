cmake_minimum_required(VERSION 3.30)
project(STLio LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)

add_subdirectory(external/Geometry)
add_subdirectory(external/googletest)

set(STLIO_SOURCES
        src/stl_model.cpp
        src/stl_reader.cpp
        src/stl_writer.cpp
        src/parsers/parser_binary.cpp
        src/parsers/parser_ascii.cpp
)

set(STLIO_HEADERS
        include/stl_model.h
        include/stl_reader.h
        include/stl_writer.h
        src/parsers/parser_binary.h
        src/parsers/parser_ascii.h
)

add_library(stl_io_lib STATIC ${STLIO_SOURCES} ${STLIO_HEADERS})
target_include_directories(stl_io_lib PUBLIC include)
target_link_libraries(stl_io_lib PUBLIC Geometry)
