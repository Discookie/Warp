
# Automatically adds all files inside these folders
# No need to update manually
file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS *.cpp)

# Set an output folder for the builds
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(WarpLib STATIC ${SRCS})

# Need to set separately for each build target
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_executable(Warp main.cpp)

# Link used libraries
target_link_libraries(WarpLib allegro_monolith-debug)
target_link_libraries(Warp WarpLib)

# Copy DLLs to /bin automatically
# It's enough to copy only the monolith
add_custom_command(
    TARGET WarpLib POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/libs/allegro/bin/allegro_monolith-debug-5.2.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

# Copy Assets into the exe's folder
add_custom_command(
    TARGET Warp PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
)
