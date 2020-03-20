# Automatically adds all files inside these folders
# No need to update manually
file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS *.cpp)

ADD_EXECUTABLE(Warp ${SRCS})

# Copy DLLs to the output folder
file(GLOB LIBRARIES "../libs/allegro/bin/*.dll")
TARGET_LINK_LIBRARIES (Warp ${LIBRARIES})
