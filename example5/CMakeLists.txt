cmake_minimum_required(VERSION 3.16)
 
find_package(YARP COMPONENTS os sig REQUIRED)
 
 
add_executable(sender)
target_sources(sender PRIVATE sender.cpp SharedData.cpp)
target_include_directories(sender PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sender PRIVATE YARP::YARP_os
                                     YARP::YARP_sig
                                     YARP::YARP_init)