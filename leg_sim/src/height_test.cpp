#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include "std_msgs/Float64.h"

ros::Publisher l_pub;
ros::Publisher h_pub;

void joint_states_callback(const sensor_msgs::JointState::ConstPtr& jointstate_msg)
{
  std_msgs::Float64 h_command;
  std_msgs::Float64 l_command;
  float theta_l_command;
  float theta_h_command;
 
  if(jointstate_msg->position[1] < 0.1 && jointstate_msg->position[0] < 0.1)
  {
    theta_l_command = 0.523;
    theta_h_command = 2.0944;
    l_command.data = theta_l_command;
    h_command.data = theta_h_command;
    h_pub.publish(h_command);
    l_pub.publish(l_command);
  }


  if(jointstate_msg->position[1] < 0.525 && jointstate_msg->position[1] > 0.519 && jointstate_msg->position[0] > 2.084 && jointstate_msg->position[0] < 2.104)
  {
    theta_l_command = 1.0472;
    theta_h_command = 1.0472;
    l_command.data = theta_l_command;
    h_command.data = theta_h_command;
    
    h_pub.publish(h_command);
    l_pub.publish(l_command);
  }
  else if(jointstate_msg->position[1] > 1.045 && jointstate_msg->position[1] < 1.049 && jointstate_msg->position[0] > 1.045 && jointstate_msg->position[0] < 1.049)
  {
    theta_l_command = 0.523;
    theta_h_command = 2.0944;
    l_command.data = theta_l_command;
    h_command.data = theta_h_command;
    
    h_pub.publish(h_command);
    l_pub.publish(l_command);
  }
  else
  {}
}

int main(int argc, char** argv){

  ros::init(argc, argv, "height_test");
  ros::NodeHandle n;

  l_pub = n.advertise<std_msgs::Float64>("/one_leg/leg_l_controller/command", 1);
  h_pub = n.advertise<std_msgs::Float64>("/one_leg/leg_h_controller/command", 1);
  ros::Subscriber joints_sub = n.subscribe("/one_leg/joint_states", 1, joint_states_callback);

  ros::spin();
  return 0;
}
