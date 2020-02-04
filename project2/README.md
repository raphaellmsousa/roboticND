### This is the solution for the project "Go chase it!"

#### The idea

It was created the cam_ball_detection node. Inside of this node, it was written the "cam_node.py" script. This one uses OpenCV (written in python) to detect the white ball and to find the center. So, after the detection, the center of the ball, as well as the area of the detected figure is published in the following topics:

```sh
/ball_center
/ball_area
```

After all, the node ball_chaser is used to send commands to the robot in the gazebo simulator. To follow the ball, it was developed a proportional controller that is responsible to calculate the angular speed to maintain the ball in the middle of the cam image. The proportional controller can be found as follow:

```sh
float referencePosition = 400 / 2; //middle of the image
float angularSpeedLimit = 1.0;
float proportionalGain = 0.01;
float error = referencePosition - ball_pose.data;
float angularVelocity = proportionalGain * error; //Proportional controller
```

## Instructions

##### 1. Create a catking workspace:
```sh
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src
catkin_init_workspace
```
##### 2. Clone and download this repository package to your ROS Workspace src folder (../catkin_ws/src) with the name rosi_defy_forros:
```sh
$ cd ~/catkin_ws/
$ git clone https://github.com/raphaellmsousa/roboticND.git 
$ catkin_make

```
##### 3. Launch the robot inside your world

This can be done by launching the world.launch file:

```sh
$ cd /home/workspace/catkin_ws/
$ source devel/setup.bash
$ roslaunch my_robot world.launch
```

##### 4. Run the ball's detection node

```sh
$ cd /home/workspace/catkin_ws/
$ source devel/setup.bash
$ roslaunch cam_ball_detection ball_detection.launch 
```

##### 5. Run drive_bot and process_image

This can be done by executing ball_chaser.launch:

```sh
$ cd /home/workspace/catkin_ws/
$ source devel/setup.bash
$ roslaunch ball_chaser ball_chaser.launch
```
