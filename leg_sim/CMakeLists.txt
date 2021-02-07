cmake_minimum_required(VERSION 3.0.2)
project(leg_sim)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
	roscpp
	std_msgs
	sensor_msgs
	message_generation
	controller_manager
)


 generate_messages(
   DEPENDENCIES
   std_msgs  # Or other packages containing msgs
   sensor_msgs
 )


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES leg_sim
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

include_directories(
 include
 ${catkin_INCLUDE_DIRS}
)

add_executable(height_test src/height_test.cpp)
target_link_libraries(height_test ${catkin_LIBRARIES})
add_dependencies(height_test leg_sim_generate_messages_cpp)

add_executable(height_ik src/height_ik.cpp)
target_link_libraries(height_ik ${catkin_LIBRARIES})
add_dependencies(height_ik leg_sim_generate_messages_cpp)

add_executable(loco_angle_ik src/loco_angle_ik.cpp)
target_link_libraries(loco_angle_ik ${catkin_LIBRARIES})
add_dependencies(loco_angle_ik leg_sim_generate_messages_cpp)
