#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

void setDestination(float x, float y, float w);

move_base_msgs::MoveBaseGoal goal;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Update Robot Status using paramter server
  ros::param::set("/robot_coord", "Start_Point");
  
  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  setDestination(6.69, 5.67, -0.00143);

  ros::Duration(5.0).sleep();

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending location of first goal");
  ac.sendGoal(goal);

   // Update Robot Status using paramter server
  ros::param::set("/robot_coord", "Move_To_Pick");
  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Package picked up!");
        // Update Robot Status using paramter server
    ros::param::set("/robot_coord", "Picked_Up");
  }
  else{
    ROS_INFO("The base failed to move forward for some reason");
        // Update Robot Status using paramter server
    ros::param::set("/robot_coord", "Faild_Pick");
    return 0;
  }

  ros::Duration(5.0).sleep();

  setDestination(9.63, 6.53, -0.00143);

  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending location of second goal");
  ac.sendGoal(goal);

  // Update Robot Status using paramter server
  ros::param::set("/robot_coord", "Move_To_Drop");
  
  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Robot has reached the dropper off zone, mission concluded!");
     // Update Robot Status using paramter server
    ros::param::set("/robot_coord", "Dropped_Off");
  }
  else{
    ROS_INFO("The base failed to move backward for some reason");
        // Update Robot Status using paramter server
    ros::param::set("/robot_coord", "Failed_Drop");
    }

  return 0;
}

void setDestination(float x, float y, float w){ 
  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = x;
  goal.target_pose.pose.position.y = y;
  goal.target_pose.pose.orientation.w = w;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal at x: %f, y: %f, w: %f",
  goal.target_pose.pose.position.x,
  goal.target_pose.pose.position.y,
  goal.target_pose.pose.orientation.w
  );
}
