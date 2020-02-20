#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = 6.69;
  goal.target_pose.pose.position.y = 5.67;
  goal.target_pose.pose.orientation.w = -0.00143;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending first goal at x: %f, y: %f, w: %f",
    goal.target_pose.pose.position.x,
    goal.target_pose.pose.position.y,
    goal.target_pose.pose.orientation.w
    );
    
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("The robot has reached the first goal");
  else
    ROS_INFO("The base failed to move for some reason");

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
    // Define a position and orientation for the robot to reach
    goal.target_pose.pose.position.x = 9.63;
    goal.target_pose.pose.position.y = 6.53;
    goal.target_pose.pose.orientation.w = -0.00143;

   // Send the goal position and orientation for the robot to reach
    ROS_INFO("Sending secound goal at x: %f, y: %f, w: %f",
    goal.target_pose.pose.position.x,
    goal.target_pose.pose.position.y,
    goal.target_pose.pose.orientation.w
    );
    
    ac.sendGoal(goal);

    // Wait an infinite time for the results
    ac.waitForResult();

    // Check if the robot reached its goal
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("That's all! Final destination!");
    else
      ROS_INFO("The base failed to move for some reason");
    }
  return 0;
}
