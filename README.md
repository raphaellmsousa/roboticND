# Udacity Map My World project

This is the link for the rtabmap.db file:

https://drive.google.com/file/d/14Uo_zJjSx4gZxx5RL3HivcGSlUMh5o5D/view?usp=sharing

## Instructions

##### 1. Install all required packages:

``` bash
$ sudo apt-get install ros-kinetic-rtabmap ros-kinetic-rtabmap-ros 
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

##### 5. Run the teleop Keyboard node:

```sh
$ cd /home/workspace/catkin_ws/
$ source devel/setup.bash
$ roslaunch my_robot teleop.launch
```

##### 6. Run the mapping node:

```sh
$ cd /home/workspace/catkin_ws/
$ source devel/setup.bash
$ roslaunch my_robot mapping.launch
```

If you want to perform localization by using the generated map (step 6), you can launch the localization node as follow:

##### 7. Run the localization node:

```sh
$ cd /home/workspace/catkin_ws/
$ source devel/setup.bash
$ roslaunch my_robot localization.launch
```



