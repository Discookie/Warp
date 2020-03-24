
# Automatically adds all files inside these folders
# No need to update manually
file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS *.cpp)

# Set an output folder for the new executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

ADD_EXECUTABLE(Warp ${SRCS})

# Link used libraries
# TARGET_LINK_LIBRARIES (Warp stdc++fs)
TARGET_LINK_LIBRARIES (Warp allegro_monolith-debug)

# Copy DLLs to the exe's folder
# It's enough to link only the monolith
file(GLOB LIBRARIES "../libs/allegro/bin/allegro_monolith-debug*.dll")
# TARGET_LINK_LIBRARIES (Warp ${LIBRARIES})
foreach(CurrentDLL IN LISTS LIBRARIES)
    add_custom_command(
        TARGET Warp PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CurrentDLL} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )
endforeach()

# Copy Assets into the exe's folder
add_custom_command(
    TARGET Warp PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
)
