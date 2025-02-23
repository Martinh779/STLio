cmake_minimum_required(VERSION 3.30)
project(STLio)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 26)

# Define the include directory
include_directories(include)

# Define the source files
set(SOURCES
        main.cpp
        src/stlio.cpp
        src/stl_model.cpp
        src/stlio_reader.cpp
        src/stlio_utils.cpp
        src/stlio_writer.cpp
)

# Define the header files
set(HEADERS
        include/stlio.h
        include/stlio_reader.h
        include/stlio_writer.h
        include/stlio_utils.h
        include/stl_model.h
)

# Add the executable
add_executable(STLio ${SOURCES} ${HEADERS})