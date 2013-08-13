cmake_minimum_required(VERSION 2.8.3)
project(corbatest)

find_package(catkin REQUIRED)

find_package(OROCOS-RTT REQUIRED)
include(${OROCOS-RTT_USE_FILE_PATH}/UseOROCOS-RTT.cmake )
find_package(PkgConfig REQUIRED)

include_directories(
  ${Boost_INCLUDE_DIR}
  ${catkin_INCLUDE_DIRS}
  )

orocos_use_package( ocl-taskbrowser )
orocos_use_package( ocl-deployment )
orocos_use_package( ocl-logging )
orocos_use_package( orocos-rtt-corba )
orocos_use_package( rtt-transport-corba )
orocos_use_package( rtt-typekit )

add_definitions(-DRTT_STATIC)
orocos_executable(server server.cpp)
orocos_executable(client client.cpp)

orocos_generate_package()

