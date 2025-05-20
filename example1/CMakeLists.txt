cmake_minimum_required(VERSION 3.5)
project(example1)

find_package(YARP REQUIRED)

add_executable(sender sender.cpp)
add_executable(receiver receiver.cpp)

target_link_libraries(sender ${YARP_LIBRARIES})
target_link_libraries(receiver ${YARP_LIBRARIES})

target_include_directories(sender PRIVATE ${YARP_INCLUDE_DIRS})
target_include_directories(receiver PRIVATE ${YARP_INCLUDE_DIRS})
