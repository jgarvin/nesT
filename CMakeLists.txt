cmake_minimum_required(VERSION 2.6)
project(nesT)

find_package(Qt4 REQUIRED)
set( Boost_ADDITIONAL_VERSIONS "1.37" "1.37.0" )
find_package(Boost 1.37 COMPONENTS thread filesystem system REQUIRED)
find_package ( SDL REQUIRED )

# Just use whatever sources are in the folder, if you don't want something
# to build move it out of the way!
file (GLOB HEADER_FILES *.h *.hpp)
file (GLOB CPP_FILES *.c *.cpp)
file (GLOB UI_FILES *.ui)

# Turn on all warnings
ADD_DEFINITIONS(-Wall)

ADD_EXECUTABLE(nesT ${CPP_FILES})

# Note QT's INCLUDE line takes care of the include_directories call for us
include_directories( ${Boost_INCLUDE_DIRS} ${SDL_INCLUDE_DIR} )
INCLUDE(${QT_USE_FILE})

# Note: Boost_LIBRARIES doesn't seem to be reliable, specify them individually
target_link_libraries(nesT ${QT_LIBRARIES}
						   ${Boost_THREAD_LIBRARY}
						   ${Boost_FILESYSTEM_LIBRARY}
						   ${Boost_SYSTEM_LIBRARY}
						   ${SDL_LIBRARY}
						   SDLmain)
