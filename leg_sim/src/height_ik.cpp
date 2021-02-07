#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <cmath>

ros::Publisher l_pub;
ros::Publisher h_pub;

const float leg_length = 0.25;

void height_command_callback(const std_msgs::Float64::ConstPtr& height_command_received)
{
  if(height_command_received->data > 0.433 || height_command_received->data < 0)
  {
    ROS_INFO("Height request is out of acceptable bounds, please enter height (in m) between 0 and 0.433");
  }
  else
  {
    std_msgs::Float64 h_command;
    std_msgs::Float64 l_command;
    float theta_l_command;
    float theta_h_command;
    float theta_t_command;

    float Hx = (height_command_received->data)/2;
    
    theta_l_command = std::asin(Hx/leg_length);

    theta_t_command = theta_l_command;
    theta_h_command = theta_t_command + theta_l_command;
    
    l_command.data = theta_l_command;
    h_command.data = 3.14159 - theta_h_command;

    l_pub.publish(l_command);
    h_pub.publish(h_command);
  }
}

int main(int argc, char** argv){

  ros::init(argc, argv, "height_ik");
  ros::NodeHandle n;

  l_pub = n.advertise<std_msgs::Float64>("/one_leg/leg_l_controller/command", 1);
  h_pub = n.advertise<std_msgs::Float64>("/one_leg/leg_h_controller/command", 1);
  ros::Subscriber height_sub = n.subscribe("/height_input", 1, height_command_callback);

  ros::spin();
  return 0;
}
