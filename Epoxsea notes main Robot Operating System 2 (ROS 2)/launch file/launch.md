# Create a launch file

Creating a launch file allows you to run multiple nodes at **once**.

### Go to your workspace

````bash
cd src
ros2 pkg create my_robot_bringup
cd my_robot_bringup
rm -rf src
rm -rf include
mkdir launch
cd launch
touch robot.launch.py
````

### Go to CMakeList.txt, add the following above `ament_package()`

````CMake
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)
````

### Go to package.xml, add packages

````xml
  <exec_depend>my_py_pkg</exec_depend>
````

### Go to robot.launch.py,copy, paste and edit

````py
from launch import LaunchDescription
from launch_ros.actions import Node
def generate_launch_description():
    ld = LaunchDescription()
    node_1 = Node(
        package = "",
        executable = ""
    )
    node_2 = Node(
        package = "",
        executable = ""
    )
    
    ld.add_action(node_1)
    ld.add_action(node_2)
    
    return ld
````

### Last step

````bash
colcon build --packages-select my_robot_bringup
ros2 laucnh my_robot_bringup robot.launch.py
````
