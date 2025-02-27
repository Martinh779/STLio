cmake_minimum_required(VERSION 3.30)
project(STLio)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 26)

# Define the include directory
include_directories(include)

# Define the source files for the library (this will be shared between main and tests)
set(LIBRARY_SOURCES
        src/stl_model.cpp
        src/stl_reader.cpp
        src/stl_writer.cpp
        src/parsers/parser_binary.cpp
        src/parsers/parser_ascii.cpp
)

# Define the header files (same as before)
set(HEADERS
        include/stl_reader.h
        include/stl_writer.h
        include/utils.h
        include/stl_model.h
        src/parsers/parser_binary.h
        src/parsers/parser_ascii.h
)

# Create the library (shared between both executable and test)
add_library(stl_io_lib STATIC ${LIBRARY_SOURCES} ${HEADERS})

# Add the main executable
add_executable(STLio main.cpp ${LIBRARY_SOURCES} ${HEADERS})

# Link the library to the main executable
target_link_libraries(STLio stl_io_lib)

# Enable testing
enable_testing()

# Add Google Test as a submodule
add_subdirectory(third_party/googletest)

# Create a test executable
set(TEST_SOURCES tests/test_stl_reader.cpp tests/test_stl_writer.cpp tests/test_utils.h tests/test_utils.cpp)

add_executable(runTests ${TEST_SOURCES})

# Link the library to the test executable
target_link_libraries(runTests stl_io_lib gtest gtest_main pthread)

# Register tests
add_test(NAME runTests COMMAND runTests)
