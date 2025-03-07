cmake_minimum_required(VERSION 2.8.3)
project(sam_uavcan_bridge)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++11")

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  uavcan_ros_bridge
  uavcan_ros_msgs
  geometry_msgs
  sensor_msgs
  std_msgs
  std_srvs
  sam_msgs
  smarc_msgs
  message_generation
  message_runtime
)

find_library(UAVCAN_LIB uavcan libuavcan_dsdlc REQUIRED)

#set(UAVCAN_DSDL_DEFINITIONS "/usr/local/share/uavcan/dsdl/uavcan") # For Linux, if the library is installed

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend tag for "message_generation"
##   * add a build_depend and a run_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
##     but can be declared for certainty nonetheless:
##     * add a run_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   std_msgs  # Or other packages containing msgs
# )

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a run_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include dsdl/dsdlc_generated
#  LIBRARIES sam_uavcan_bridge
  CATKIN_DEPENDS uavcan_ros_bridge
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  dsdl/dsdlc_generated
  ${catkin_INCLUDE_DIRS}
)

add_custom_target(sam_dsdlc ${DSDL_COMPILER} # If the library is installed
                  "smarc_uavcan_messages" "smarc_uavcan_services" -I${UAVCAN_DSDL_DEFINITIONS}
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dsdl)

## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/sam_uavcan_bridge.cpp
# )
add_library(sam_uavcan_platform_linux
  src/uavcan_platform_linux.cpp
)

add_library(uav_to_ros_actuator_status
  src/uav_to_ros/actuator_status.cpp
)

add_library(uav_to_ros_leak
  src/uav_to_ros/leak.cpp
)

add_library(uav_to_ros_sensor_pressure_stamped
  src/uav_to_ros/sensor_pressure_stamped.cpp
)

add_library(uav_to_ros_servo_feedback_double
  src/uav_to_ros/servo_feedback_double.cpp
)

add_library(uav_to_ros_temperature
  src/uav_to_ros/temperature.cpp
)

add_library(uav_to_ros_battery_state_basic
  src/uav_to_ros/battery_state_basic.cpp
)

add_library(uav_to_ros_battery_info
  src/uav_to_ros/battery_info.cpp
)

add_library(uav_to_ros_consumed_charge_feedback
  src/uav_to_ros/consumed_charge_feedback.cpp
)

add_library(uav_to_ros_consumed_charge_array
  src/uav_to_ros/consumed_charge_array.cpp
)

add_library(uav_to_ros_ctd_feedback
  src/uav_to_ros/ctd_feedback.cpp
)

add_library(uav_to_ros_thruster_feedback_id
  src/uav_to_ros/thruster_feedback_id.cpp
)

add_library(uav_to_ros_circuit_status_stamped
  src/uav_to_ros/circuit_status_stamped.cpp
)

add_library(uav_to_ros_panic
  src/uav_to_ros/panic.cpp
)

add_library(ros_to_uav_percent_stamped
  src/ros_to_uav/percent_stamped.cpp
)

add_library(ros_to_uav_ballast_angles
  src/ros_to_uav/ballast_angles.cpp
)

add_library(ros_to_uav_dropweights
  src/ros_to_uav/dropweights.cpp
)

add_library(ros_to_uav_dvl
  src/ros_to_uav/dvl.cpp
)

add_library(ros_to_uav_sss
  src/ros_to_uav/sss.cpp
)

add_library(ros_to_uav_led
  src/ros_to_uav/led.cpp
)

add_library(ros_to_uav_thruster_rpm
  src/ros_to_uav/thruster_rpm.cpp
)

add_library(ros_to_uav_thruster_rpm_id
  src/ros_to_uav/thruster_rpm_id.cpp
)

add_library(ros_to_uav_thruster_rpms
  src/ros_to_uav/thruster_rpms.cpp
)

add_library(ros_to_uav_thruster_angles
  src/ros_to_uav/thruster_angles.cpp
)

add_library(ros_to_uav_dual_thruster_rpm
  src/ros_to_uav/dual_thruster_rpm.cpp
)

add_library(ros_to_uav_light_command
  src/ros_to_uav/light_command.cpp
)

add_library(ros_to_uav_panic
  src/ros_to_uav/panic.cpp
)

add_library(ros_to_uav_uavcan_update_battery
  src/ros_to_uav/uavcan_update_battery.cpp
)

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(uav_to_ros_actuator_status ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(uav_to_ros_leak ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(uav_to_ros_sensor_pressure_stamped sam_dsdlc)
add_dependencies(uav_to_ros_servo_feedback_double sam_dsdlc)
add_dependencies(uav_to_ros_temperature ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(uav_to_ros_battery_state_basic ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(uav_to_ros_battery_info ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(uav_to_ros_consumed_charge_feedback ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(uav_to_ros_consumed_charge_array ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(uav_to_ros_ctd_feedback ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(uav_to_ros_thruster_feedback_id ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(uav_to_ros_circuit_status_stamped ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(uav_to_ros_panic ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(ros_to_uav_percent_stamped ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(ros_to_uav_ballast_angles ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(ros_to_uav_thruster_rpm ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(ros_to_uav_thruster_rpm_id ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(ros_to_uav_thruster_rpms ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(ros_to_uav_thruster_angles ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(ros_to_uav_dual_thruster_rpm ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(ros_to_uav_light_command ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(ros_to_uav_panic ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(ros_to_uav_uavcan_update_battery ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(ros_to_uav_dropweights ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(ros_to_uav_led ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(ros_to_uav_dvl ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(ros_to_uav_sss ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})


## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
# add_executable(${PROJECT_NAME}_node src/sam_uavcan_bridge_node.cpp)
add_executable(sam_uavcan_to_ros_bridge src/uavcan_to_ros_bridge.cpp)
add_executable(sam_ros_to_uavcan_bridge src/ros_to_uavcan_bridge.cpp)
add_executable(sam_uavcan_time_master src/uavcan_time_master.cpp)
add_executable(sam_uavcan_network_monitor src/uavcan_network_monitor.cpp)
add_executable(sam_ros_to_uavcan_services src/ros_to_uavcan_services.cpp)
add_dependencies(sam_uavcan_to_ros_bridge ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(sam_ros_to_uavcan_bridge ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(sam_uavcan_time_master ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(sam_uavcan_network_monitor ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(sam_ros_to_uavcan_services ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use
## e.g. "rosrun someones_pkg node" instead of "rosrun someones_pkg someones_pkg_node"
# set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
# target_link_libraries(${PROJECT_NAME}_node
#   ${catkin_LIBRARIES}
# )
target_link_libraries(sam_uavcan_to_ros_bridge
  sam_uavcan_platform_linux
  uav_to_ros_actuator_status
  uav_to_ros_leak
  uav_to_ros_sensor_pressure_stamped
  uav_to_ros_servo_feedback_double
  uav_to_ros_temperature
  uav_to_ros_battery_state_basic
  uav_to_ros_battery_info
  uav_to_ros_consumed_charge_feedback
  uav_to_ros_consumed_charge_array
  uav_to_ros_ctd_feedback
  uav_to_ros_thruster_feedback_id
  uav_to_ros_circuit_status_stamped
  uav_to_ros_panic
  #${uavcan_ros_bridge_LIBRARIES}
  ${catkin_LIBRARIES}
  #${UAVCAN_LIB}
  rt
)

target_link_libraries(sam_ros_to_uavcan_bridge
  sam_uavcan_platform_linux
  ros_to_uav_percent_stamped
  ros_to_uav_ballast_angles
  ros_to_uav_thruster_rpm
  ros_to_uav_thruster_rpm_id
  ros_to_uav_thruster_rpms
  ros_to_uav_thruster_angles
  ros_to_uav_dual_thruster_rpm
  ros_to_uav_light_command
  ros_to_uav_panic
  ros_to_uav_dropweights
  ros_to_uav_led
  ros_to_uav_dvl
  ros_to_uav_sss

  #${uavcan_ros_bridge_LIBRARIES}
  ${catkin_LIBRARIES}
  #${UAVCAN_LIB}
  #uavcan_dsdlc
  rt
)

target_link_libraries(sam_uavcan_time_master
  sam_uavcan_platform_linux
  ${catkin_LIBRARIES}
  #${UAVCAN_LIB}
  rt
)

target_link_libraries(sam_uavcan_network_monitor
  sam_uavcan_platform_linux
  ${catkin_LIBRARIES}
  #${UAVCAN_LIB}
  rt
)

target_link_libraries(sam_ros_to_uavcan_services
  sam_uavcan_platform_linux
  ros_to_uav_uavcan_update_battery
  ${catkin_LIBRARIES}
  #${UAVCAN_LIB}
  rt
)

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_sam_uavcan_bridge.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
