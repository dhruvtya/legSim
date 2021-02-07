#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/JointState.h>
#include <cmath>

ros::Publisher l_pub;
ros::Publisher h_pub;

float h_curr_angle;

void joint_states_callback(const sensor_msgs::JointState::ConstPtr& jointstate_msg)
{
  h_curr_angle = jointstate_msg->position[1];
  if(h_curr_angle>=0.698) //To make sure it is possible to satisfy the height condition
  {
    float theta_t_command, theta_h_command;
    std_msgs::Float64 h_command;
    float leg_length = 0.25;
    float Hy = 0.4068 - (0.25*(std::sin(h_curr_angle)));

    theta_t_command = std::asin(Hy/leg_length);
    theta_h_command = theta_t_command + h_curr_angle;
    h_command.data = 3.14159 - theta_h_command;
    h_pub.publish(h_command);
  }
}



void angle_command_callback(const std_msgs::Float64::ConstPtr& angle_command_received)
{
  if(angle_command_received->data > 20.0 || angle_command_received->data < -20.0)
  {
    ROS_INFO("Angle request is out of acceptable bounds, please enter height (in degrees) between -20.0 and 20.0");
  }
  else
  {
    float theta_m_command = angle_command_received->data;
    std_msgs::Float64 l_command;
    float theta_l_command = 60.0;

    l_command.data = (3.14159 * (theta_l_command + theta_m_command))/180;
    l_pub.publish(l_command); 
  }
}



int main(int argc, char** argv){

  ros::init(argc, argv, "loco_angle_ik");
  ros::NodeHandle n;

  l_pub = n.advertise<std_msgs::Float64>("/one_leg/leg_l_controller/command", 1);
  h_pub = n.advertise<std_msgs::Float64>("/one_leg/leg_h_controller/command", 1);
  ros::Subscriber angle_sub = n.subscribe("/angle_input", 1, angle_command_callback);
  ros::Subscriber joints_sub = n.subscribe("/one_leg/joint_states", 1, joint_states_callback);

  ros::spin();
  return 0;
}
