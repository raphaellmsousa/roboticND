#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main( int argc, char** argv )
{
  // Create Node
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  
  // Create Publisher
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  // Create marker
  visualization_msgs::Marker marker;

  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "add_markers";
  marker.id = 0;
  
  // Set the marker type.  can be a CUBE, SPHERE, ARROW, or CYLINDER
  marker.type = visualization_msgs::Marker::CUBE;

  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();

  // Set the pickup pose of the marker.
  // This is relative to the frame/time specified above
  marker.pose.position.x = 6.69;
  marker.pose.position.y = 5.67;
  marker.pose.position.z = 0;

  // Set the orientation of the marker.
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = -0.00143;

  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = 0.25;
  marker.scale.y = 0.25;
  marker.scale.z = 0.25;

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 0.0f;
  marker.color.g = 0.0f;
  marker.color.b = 1.0f;
  marker.color.a = 1.0f;

  marker.lifetime = ros::Duration();

  // Check for subscribers
  while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
  //ROS_INFO("Connected to Marker Subscriber");

  // Set the marker action.  Options are ADD, DELETE, or DELETEALL.
  marker.action = visualization_msgs::Marker::ADD;
  // Publish the marker
  marker_pub.publish(marker);
  ROS_INFO("Marker published at pick-up point");
  

  // check robot_coord using parameter server
  std::string robot_coord;
  ros::Rate r(1);

  while (ros::ok())
  {
    if (ros::param::get("/robot_coord", robot_coord)){
      ROS_INFO("Robot Position %s", robot_coord.c_str());

      if (robot_coord=="Picked_Up"){

          // Set the marker action to DELETE
          marker.action = visualization_msgs::Marker::DELETE;
          // Publish the marker
          marker_pub.publish(marker);
          ROS_INFO("Marker removed from pick-up point");

          // Sleep for 5 sec
          ros::Duration(5.0).sleep();
      }

      if (robot_coord=="Dropped_Off"){

          // Set the drop-off pose of the marker.
          // This is relative to the frame/time specified above
          marker.pose.position.x = 9.63;
          marker.pose.position.y = 6.53;
          marker.pose.position.z = 0;

          // Set the marker action to ADD.
          marker.action = visualization_msgs::Marker::ADD;
          // Publish the marker
          marker_pub.publish(marker);
          ROS_INFO("Marker published at drop_off point");
          // Sleep for 5 sec
          ros::Duration(5.0).sleep();
      }      
    }    
    r.sleep();
  }
   
}


