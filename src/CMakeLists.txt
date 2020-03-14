# Automatically adds all files inside these folders
# No need to update manually
file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS *.cpp)

ADD_EXECUTABLE(Warp ${SRCS})

