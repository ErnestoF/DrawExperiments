cmake_minimum_required(VERSION 2.8.11)

project(Contagion)

# Compiler settings 
set (CMAKE_CXX_COMPILER clang)
ADD_DEFINITIONS(-std=c++1y -stdlib=libc++ )
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# Find dependencies
find_package(Qt5Widgets)
find_package(Qt5Gui)
find_package(PythonLibs REQUIRED)
find_package(Boost COMPONENTS python filesystem system REQUIRED)
message( ${Boost_LIBRARIES})

# Define SOURCES 
set(CONTAGION_SOURCES 
defs.cpp
gamesession.cpp
gamestate.cpp
guessresponse.cpp
guiplayer.cpp
humanitem.cpp
main.cpp
mainwindow.cpp
moderator.cpp
randomplayer.cpp)

# Tell CMake to create the helloworld executable
add_executable(contagion  ${CONTAGION_SOURCES} Tasks.txt)

# Link.
target_link_libraries(contagion Qt5::Widgets ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} -lc++ -lc++abi -lm -lc -lgcc_s -lgcc)
