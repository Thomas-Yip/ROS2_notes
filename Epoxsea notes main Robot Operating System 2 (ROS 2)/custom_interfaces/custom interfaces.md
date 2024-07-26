# What are custom interfaces?

In ROS2, you can create tailor-made messages and service to meet your needs.

## Create a custom interfaces package

````bash
ros2 pkg create <custom_interfaces>
cd <custom_interfaces>
rm -rf include/ 
rm -rf src/
mkdir msg
mkdir srv
````

## Go to package.xml

````xml
<buildtool_depend>ament_cmake</buildtool_depend>

<build_depend>rosidl_default_generators</build_depend> <!--add--> 
<exec_depend>rosidl_default_runtime</exec_depend> <!--add--> 
<member_of_group>rosidl_interface_packages</member_of_group> <!--add--> 

<test_depend>ament_lint_auto</test_depend>

````

## Go to CMakeLists.txt

````CMake
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED) # add

````

## To create custom messages or services, go to msg folder

````bash
touch CustomMsg.msg
````

Remeber, to create a service or message, the name MUST be in **PascalCase**.

## Why?

Because ROS2 automatically generate a specific .hpp file. In the above example "CustomMsg.msg", the .hpp file would become "custom_msg.hpp".

<img width="600" alt="Screenshot 2023-08-17 at 12 04 22 AM" src="https://github.com/Epoxsea/ROS2-notes/assets/114132006/c560a9f7-a1de-4acc-a7e5-91cf938b26d9">

## Go to CustomMsg.msg

````
int64 number
string text
````

## Go to CMakeLists.txt

````CMake
rosidl_generate_interfaces(${PROJECT_NAME} # add
"msg/CustomMsg.msg" # add
) # add
ament_package()

````

## Colon build your package

````bash
colcon build --packages-select custom_interfaces
````

## Last step

Since you have created a new dependency, remember to add the dependency to the package and the followings.

<img width="1440" alt="Screenshot 2023-08-17 at 12 48 31 AM" src="https://github.com/Epoxsea/ROS2-notes/assets/114132006/5b780b79-070f-4092-8874-119655003b3b">

In the workspace, 

````bash
source install/local_setup.bash
````
