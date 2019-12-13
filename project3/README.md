# Udacity AMCL Where Am I

### This is the solution for the project "where am I"


![Output](https://github.com/raphaellmsousa/roboticND/tree/master/project3/my_robot/video_pics/gif0.gif

## Instructions

##### 1. Create a catking workspace:
```sh
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src
catkin_init_workspace
```
##### 2. Clone and download this repository package to your ROS Workspace src folder:
```sh
$ cd ~/catkin_ws/
$ git clone https://github.com/raphaellmsousa/roboticND.git 
$ catkin_make

```
##### 3. Launch the robot inside your world:

This can be done by launching the world.launch file:

```sh
$ cd /home/workspace/catkin_ws/
$ source devel/setup.bash
$ roslaunch my_robot world.launch
```

##### 4. Run the AMCL node:

This can be done by executing ball_chaser.launch:

```sh
$ cd /home/workspace/catkin_ws/
$ source devel/setup.bash
$ roslaunch my_robot amcl.launch
```




