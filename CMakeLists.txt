cmake_minimum_required(VERSION 2.6)
project(nesT)

find_package(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})

# Just use whatever sources are in the folder, if you don't want something
# to build move it out of the way!
file (GLOB HEADER_FILES *.h *.hpp)
file (GLOB CPP_FILES *.c *.cpp)
file (GLOB UI_FILES *.ui)

# Turn on all warnings
ADD_DEFINITIONS(-Wall)

ADD_EXECUTABLE(nesT ${CPP_FILES})
target_link_libraries(nesT ${QT_LIBRARIES})
