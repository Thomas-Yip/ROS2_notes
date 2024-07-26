### Please follow the instructions

````
cd ros2_resource
colcon build --packages-select turtlebot
colcon build --packages-select my_robot_bringup
. install/setup.bash // For Linux
. install/setup.zsh // For Mac
ros2 run turtlesim turtlesim_node
ros2 launch my_robot_bringup turtlebot.launch.py
````

### Goal: Killing new turtles.

* When a new turtle is spawned, move turtle1 near the new turtle and kill it. 
* Every a few seconds, a new turtle is spawned and its coordinate is published to the topic "turtle_coor".
* There is a total of 128 turtles will be spawned.
* Turtles are spawned between (0,0) to (11,11).
* You are not required to establish the spawn service.

### Demo

![ezgif com-video-to-gif](https://github.com/Epoxsea/ROS2-notes/assets/114132006/a0eda821-6519-4a51-b789-44639cc1b8e6)

### Useful information

````cpp
turtle1 // it is the only turtle that you can control.
turtle1/cmd_vel // publish your control command to this topic.
turtle1/pose // subscribe this topic to know your turtle's pose.
#include "turtlesim/srv/kill.hpp" // to establish kill service on your client side.
````
