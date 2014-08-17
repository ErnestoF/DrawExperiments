cmake_minimum_required(VERSION 2.8.11)

project(Contagion)

# Compiler settings 
set (CMAKE_CXX_COMPILER clang)
ADD_DEFINITIONS(-std=c++11) 
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

# Define SOURCES 
set(CONTAGION_SOURCES 
 gamesession.cpp 
 humanitem.cpp 
 main.cpp 
 mainwindow.cpp 
 server.cpp 
 gamestate.cpp 
 randomclient.cpp 
 guiclient.cpp 
 guessresponse.cpp 
 defs.cpp)

# Tell CMake to create the helloworld executable
add_executable(contagion  ${CONTAGION_SOURCES})

# Use the Widgets module from Qt 5.
target_link_libraries(contagion Qt5::Widgets)
