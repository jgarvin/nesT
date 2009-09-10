cmake_minimum_required(VERSION 2.6)
project(nesT)

find_package(Qt4 REQUIRED)
set( Boost_ADDITIONAL_VERSIONS "1.37" "1.37.0" )
find_package(Boost 1.37 COMPONENTS thread filesystem system REQUIRED)
find_package ( SDL REQUIRED )
find_package(Automoc4 REQUIRED)

# Just use whatever sources are in the folder, if you don't want something
# to build move it out of the way!
file (GLOB_RECURSE HEADER_FILES src/*.hpp)
file (GLOB_RECURSE CPP_FILES src/*.cpp)
file (GLOB_RECURSE UI_FILES src/*.ui)

# Turn on all warnings
ADD_DEFINITIONS(-Wall)

# Any files we find are added to the build list and run through QT4's moc system
automoc4_add_executable(nesT ${CPP_FILES})

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
