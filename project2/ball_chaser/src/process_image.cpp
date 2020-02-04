#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

#include "std_msgs/Float32.h"

std_msgs::Float32 ball_pose;
std_msgs::Float32 ball_area;

using namespace std;

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the comman_robot service to drive the robot in the
// specified direction
void drive_robot(float lin_x, float ang_z)
{
  // TODO: Request a service and pass the velocities to it to drive the robot
  ball_chaser::DriveToTarget srv;
  srv.request.linear_x = lin_x;
  srv.request.angular_z = ang_z;
  client.call(srv);

  cout << "The linear speed is: " << lin_x << "The angular speed is: " << ang_z << "\n";
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

  int white_pixel = 255;

  // TODO: Loop through each pixel in the image and check if there's a bright white one
  // Then, identify if this pixel falls in the left, mid, or right side of the image
  // Depending on the white ball position, call the drive_bot function and pass velocities to it
  // Request a stop when there's no white ball seen by the camera

  // The ball's detection has been done in the cam_ball_detection node
  float referencePosition = 400 / 2; //middle of the image
  float angularSpeedLimit = 1.0;
  float proportionalGain = 0.01;
  float error = referencePosition - ball_pose.data;
  float angularVelocity = proportionalGain * error; //Proportional controller

  //Angular speed limitation
  if (angularVelocity >= angularSpeedLimit)
    angularVelocity = angularSpeedLimit;
  else if (angularVelocity < 0.0 && angularVelocity <= -angularSpeedLimit)
    angularVelocity = -angularSpeedLimit;
  else{
    angularVelocity = angularVelocity;
  }

  //Avoid hitting the ball
  if(ball_area.data<=58000 && ball_area.data>0)
    drive_robot(0.2, angularVelocity);
  else if(ball_area.data==0)
    drive_robot(0.0, 0.0);
  else
    drive_robot(0.0, 0.0);
}

void ball_position_callback(const std_msgs::Float32::ConstPtr & pose_message)
{
  ball_pose.data = pose_message->data;
}

void ball_area_callback(const std_msgs::Float32::ConstPtr & pose_message)
{
  ball_area.data = pose_message->data;
}

int main(int argc, char** argv)
{
  // Initialize the process_image node and create a handle to it
  ros::init(argc, argv, "process_image");
  ros::NodeHandle n;

  // Define a client service capable of requesting services from command_robot
  client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

  // Subscribe to /camera/rgb/image_raw topic to read the image data inside the
  // process_image_callback function
  ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

  ros::Subscriber sub2 = n.subscribe("/ball_center", 10, ball_position_callback);

   ros::Subscriber sub3 = n.subscribe("/ball_area", 10, ball_area_callback);

  // Handle ROS communication events
  ros::spin();

  return 0;
}