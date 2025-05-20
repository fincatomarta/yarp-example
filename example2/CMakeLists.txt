cmake_minimum_required(VERSION 3.5)
project(hello_module)

find_package(YARP REQUIRED)
include_directories(${YARP_INCLUDE_DIRS})
add_executable(hello_module hello_module.cpp)
target_link_libraries(hello_module ${YARP_LIBRARIES})
