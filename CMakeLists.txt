cmake_minimum_required (VERSION 3.8)

project ("Warp")
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_GENERATOR_PLATFORM=x64)


# Dependencies
add_subdirectory (libs/googletest)
# Neither doesn't have any build deps

# Add include directories
include_directories (libs/allegro/include)
include_directories (libs/googletest/googletest/include)
include_directories (libs/googletest/googlemock/include)
include_directories (libs/neither/include)

# Add link directories (for precompiled packages)
link_directories (libs/allegro/lib)

# Add the project itself
include_directories (src)
add_subdirectory (src)