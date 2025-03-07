#include <sam_uavcan_bridge/ros_to_uav/sss.h>

namespace ros_to_uav {

template <>
bool convert(const std_msgs::Bool& ros_msg, uavcan::equipment::actuator::ArrayCommand& uav_msg, unsigned char uid)
{
    // const std::string sub = ros_msg.data.substr(0, 7);
    // const char* c = sub.c_str();
    // uav_msg.reason_text = c;

    const bool boolean = ros_msg.data;//.substr(0, 7);
    // const char* c = sub.c_str();

    uav_msg.commands.resize(1);
    
    uav_msg.commands[0].actuator_id = uid;
    uav_msg.commands[0].command_value = boolean;//c;
    uav_msg.commands[0].command_type = uavcan::equipment::actuator::Command::COMMAND_TYPE_POSITION;
    return true;
}

}
