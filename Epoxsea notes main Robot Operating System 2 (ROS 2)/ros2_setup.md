# ROS2 setup

## Install

* ROS
* XML
* CMake

## Then , shift+ctrl+p, choose the first shown in the Command Palette, which is ROS:Update C++ Properties

## Useful commands

## Go back

````
cd ..
````

## Go to root

````
cd
````

## Change directory

````
cd DIRECTORY
````

## List the following paths

````
ls
````

## Create a file

````
touch foo.cpp
````

## Make a directory

````
mkdir DIRECTORY
````

## Create a ROS2 package

````
ros2 pkg create my_cpp_pkg --build-type ament_cmake --dependencies rclcpp 
````

## Build packages

````
colcon build
````

## Build a specific package

````
colcon build --packages-select my_cpp_pkg
````

## Source a workspace

````
. install/setup.bash
````

## Run an executable

````
ros2 run my_cpp_pkg first
````

## Show all the topics

````
ros2 topic list
````

## Echo a topic

````
ros2 topic echo /TOPIC_NAMW
````

## Obtain the interface type of a topic

````
ros2 topic info /TOPIC_NAME
````

## Know the format of the interface (example_interfaces/msg/Bool)

````
ros2 interface show example_interfaces/msg/Bool
````

## See the connections between all the nodes

````
rqt_graph
````
