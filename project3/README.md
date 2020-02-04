# Udacity AMCL Where Am I

Check the results in the video_pics folder

## Instructions

##### 1. Install all required packages:

First, for a native application, we must install the navigation stack package as follow:

``` bash
$ sudo apt-get install ros-kinetic-navigation
$ sudo apt-get install ros-kinetic-map-server
$ sudo apt-get install ros-kinetic-move-base
$ rospack profile
$ sudo apt-get install ros-kinetic-amcl
```

##### 2. Create a catking workspace:
```sh
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src
catkin_init_workspace
```
##### 3. Clone and download this repository package to your ROS Workspace src folder:
```sh
$ cd ~/catkin_ws/
$ git clone https://github.com/raphaellmsousa/roboticND.git 
$ catkin_make

```
##### 4. Launch the robot inside your world:

This can be done by launching the world.launch file:

```sh
$ cd /home/workspace/catkin_ws/
$ source devel/setup.bash
$ roslaunch my_robot world.launch
```

##### 5. Run the AMCL node:

This can be done by executing ball_chaser.launch:

```sh
$ cd /home/workspace/catkin_ws/
$ source devel/setup.bash
$ roslaunch my_robot amcl.launch
```




