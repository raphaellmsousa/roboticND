#!/bin/sh
cd ..
xterm  -e  "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(pwd)/worlds/raphaell.world" &
#xterm  -e  "roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 3
xterm  -e  "roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(pwd)/map/map_mod.yaml" &
#xterm  -e  "roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 3
xterm  -e  "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 3
xterm  -e  "rosrun pick_objects pick_objects"
