cmake_minimum_required(VERSION 3.0)

# Set an output folder for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(Google_Tests main.cpp SceneTest.cpp ModelTest.cpp)

target_link_libraries(Google_Tests
        WarpLib
        gtest
        gtest_main)
