#ifndef ROS_TO_UAV_LED_H
#define ROS_TO_UAV_LED_H

#include <uavcan/equipment/actuator/ArrayCommand.hpp>
#include <uavcan_ros_bridge/uavcan_ros_bridge.h>
#include <std_msgs/Bool.h>

namespace ros_to_uav {

template <>
bool convert(const std_msgs::Bool& ros_msg,uavcan::equipment::actuator::ArrayCommand& uav_msg, unsigned char uid);

}

#endif
