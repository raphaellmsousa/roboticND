[![Udacity - Robotics NanoDegree Program](https://s3-us-west-1.amazonaws.com/udacity-robotics/Extra+Images/RoboND_flag.png)](https://www.udacity.com/robotics)

# Udacity Home Service Robot 

This is the final project of the Robot Nanodegree from Udacity. The main goal is coding a Home Service Robot to pick up and delivery a package autonomously. As follow, it will be presented the start up of the proposed solution for this project:

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
$ git clone https://github.com/raphaellmsousa/roboticND.git 
$ cd ..
$ catkin_make
```

Obs.: inside of the roboticND folder (from the repository), it is already included the follow ROS packages:

```sh
$ git clone https://github.com/ros-perception/slam_gmapping
$ git clone https://github.com/turtlebot/turtlebot
$ git clone https://github.com/turtlebot/turtlebot_interactions
$ git clone https://github.com/turtlebot/turtlebot_simulator
```

Obs2.: the above packages provided in this repository has some minor changes for this project, but should work with the original ones.

Obs3.: the above ROS packages are submodules, so, to push them to a repository, it is necessary to delete the .git folders from these submodules.

##### 4. Start the shell scripts:

This can be done as follow:

```sh
$ cd /home/workspace/catkin_ws/
$ source devel/setup.bash
$ cd src/scripts/
$ chmod +x home_service.sh
$ ./home_service.sh
```

##### 5. Results

<p align="center">
    <img src="./figs/project5.png" width="1200" height="720" title="Home Service Robot">
</p> 





