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

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  setDestination(6.69, 5.67, -0.00143);

  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("The robot has reached the second goal");
    ros::Duration(5.0).sleep();
    //std::cin.get(); //we need press enter to move on
  }
  else{
    ROS_INFO("The base failed to move for some reason");
    ros::Duration(5.0).sleep();
    //std::cin.get();
  }

  setDestination(9.63, 6.53, -0.00143);

  ac.sendGoal(goal);

  ac.waitForResult();
  
  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("The robot has reached the second goal");
    ros::Duration(5.0).sleep();
    //std::cin.get();
  }
  else{
    ROS_INFO("The base failed to move for some reason");
    ros::Duration(5.0).sleep();
    //std::cin.get();
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