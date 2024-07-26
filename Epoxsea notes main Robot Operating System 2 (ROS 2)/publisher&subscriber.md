# Learn these commands if you don't know

https://www.geeksforgeeks.org/basic-linux-commands/


````
sudo apt update
sudo apt install python3-colcon-common-extensions
gedit ~/.bashrc
source /usr/share/colcon_argcomplete/hook/colcon-argcomplete.bash // put it at the bottom of bashrc
source /opt/ros/humble/setup.bash // put it at the bottom of bashrc
````

In ros2, we use node and topic to control the robot. Essentially, topic is used to exchange data and node is the place to process the data.   
Before we creating nodes, we usually create multiple packages to contain all the nodes and a src to contain all the packages.   
![rosgraph](https://github.com/Epoxsea/ROS2-notes/assets/114132006/7908ddf2-c5a7-4a35-a375-9d8c0686d0bb)

# Create a workspace

````
mkdir ros2_ws // crate folder
cd ros2_ws // go to folder
mkdir src // create src folder(folder)
cd src // go to src
ros2 pkg create my_cpp_pkg --build-type ament_cmake --dependencies rclcpp // create package
cd src // go to src inside the package
touch foo.cpp // create a file
chmod +x foo.cpp // make the file executable
````

Inside a node, you can create subscrption and publishers to access and publish data.
For example, in gazebo simulator, all the information such as gps, imu are provided by the topics, you can create subscriptions to subscribe these topics to get the data. Using topics and nodes facilitate data exchange.

### Basic node structure

1. include header files, which are rclcpp and some interfaces you use.
1. create a node (class). Inside a the class, it's the place you process the data and control the robot
1. int main(); execute the node.

### Interfaces

Iinterface are important for data exchange between subscriptions, publishers and topics. Basically, it's similar to data type (int, bool). You can use the interfaces provided by ros2 or create one by yourselves(self-study,note is provided). Note that you should be careful
with the interfaces before creating subscription and publisher.

### Comman interfaces

* std_msgs
* example_interfaces

How to know the interface of a topic?

````
ros2 topic info /<topic_name>
````

How to know the format of an interface? (If the interface name is "geometry_msgs/msg/twist.hpp")

````
ros2 topic show geometry_msgs/msg/Twist
````

### Related commands

````
ros2 topic list (list all the topics) 
ros2 topic echo /topic_name (echo a topic)
rqt_graph (a gui to show the connections between nodes and topics) 
````

### Create a subscription

To subsribe something, you need to create a subscription in public.

````cpp
 sub_thrust = this->create_subscription<std_msgs::msg::Float64>("wamv/thrust",10,
                                                                std::bind(&ControlNode::thrust_callback,this,std::placeholders::_1));  // inteface name, topic name, qos (usually 10 + idk the meaning), callback function)
````

Why we need to callback function?   
You may want to use the obtain the data for any purposes such as assign the value of a data to a variable, use the data to do calculation.   
It is always recommended to assign the value of the data to a variable before taking any actions.   
Inside private, create a callback function to collect the data. 

````cpp
 void thrust_callback(const std_msgs::msg::Float64::SharedPtr msg){ // need to pick the correct intefface first
        power = msg->data; // power is a data member in private
        RCLCPP_INFO(this->get_logger(),"%f",msg->data); // Never do it, it may result in error.
    }
````

### Create a publisher

To publish something, create a publisher and a timer in public publish the data.

````cpp
publisher = this->create_publisher<example_interfaces::msg::Int64>("number",10); // interface, topic name, qos
timer_ = this->create_wall_timer(std::chrono::seconds(1),     // set timer frequency (seconds/milliseconds). What is the frequency you want to send a message?
                                        std::bind(&NumberPublisher::func,this)); // call function (func) 
````

Inside private, create a function which generate the data you want to publish.

````cpp
void func(){
        auto msg = example_interfaces::msg::Int64(); // decide the interface of the msg
        msg.data = std::int64_t(number); // assign a value to the msg
        // or
        int foo = 123;
        msg.data = foo;
        publisher->publish(msg); // publish the message
    }
````

### At last, for all the objects you created in public (publisher, subscription, timer), add them in the private

````cpp
    rclcpp::TimerBase::SharedPtr timer_; // timer_ is the name of timer you created before
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher; // publisher is the name of the publisher you created before
    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr sub_thrust; // sub_thrust is the name of the subscription you created before
````

# Tips: Just follow the syntax

# Next step, add executables and dependencies(if you use a new interface)

### Add dependencies in the package.xml

For the all the dependencies you included, you need to add them in package.xml( <depend>blah_blah_blah<depend> )

````
<?xml version="1.0"?>
<?xml-model href="http://download.ros.org/schema/package_format3.xsd" schematypens="http://www.w3.org/2001/XMLSchema"?>
<package format="3">
  <name>my_cpp_pkg</name>
  <version>0.0.0</version>
  <description>TODO: Package description</description>
  <maintainer email="ubuntu@todo.todo">ubuntu</maintainer>
  <license>TODO: License declaration</license>

  <buildtool_depend>ament_cmake</buildtool_depend>

  <depend>rclcpp</depend>
  <depend>example_interfaces</depend>
  <depend>std_msgs</depend>
  <depend>ros_gz_interfaces</depend>
  <test_depend>ament_lint_auto</test_depend>
  <test_depend>ament_lint_common</test_depend>

  <export>
    <build_type>ament_cmake</build_type>
  </export>
</package>


````

### In cmakelist, you need to add executables of your nodes.

1. find_package(blah_blah_blah REQUIRED) // Put the dependencies you used here
1. add executable (If the file and node name is "first") + ament_target_dependencies()

````cpp
 add_executable(first src/first.cpp) // (executable name, file name)
  ament_target_dependencies(first rclcpp example_interfaces) // (executable name, dependencies)
````

4. put all the executables inside install 

````
   install(TARGETS # install executable into the workspace
   first
   DESTINATION lib/${PROJECT_NAME}
   )
````

````
cmake_minimum_required(VERSION 3.8)
project(my_cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(std_msgs REQUIRED)
find_package(ros_gz_interfaces REQUIRED)
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()
add_executable(first src/first.cpp)
ament_target_dependencies(first rclcpp example_interfaces std_msgs)
install(TARGETS # install executable into the workspace

  first
  DESTINATION lib/${PROJECT_NAME}

)
ament_package()

````

# At last, compilation

1. Go back to workspace
1. colcon build OR colcon build --packages-select \<package_name>
1. . install/setup.bash (source the workspace)
1. ros2 run \<package_name> \<executable_name>
1. self-study topic: launch(written)+parameter( https://foxglove.dev/blog/how-to-use-ros2-parameters) (quite easy)

````cpp
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"
#include "std_msgs/msg/float32.hpp"
#include "ros_gz_interfaces/msg/param_vec.hpp"
class NumberPublisher: public rclcpp::Node
{
    public:
        NumberPublisher(): Node("NumberPublisher"){

        publisher = this->create_publisher<example_interfaces::msg::Int64>("number",10);
        subscriber = this->create_subscription<example_interfaces::msg::Int64>("number",10,std::bind(&NumberPublisher::number_callback,this,std::placeholders::_1));
        sub_wind = this->create_subscription<std_msgs::msg::Float32>("/vrx/debug/wind/speed",10,std::bind(&NumberPublisher::windSpeed_callback,this,std::placeholders::_1));

        timer_ = this->create_wall_timer(std::chrono::seconds(1),     // set timer frequency
                                        std::bind(&NumberPublisher::func,this)); // call function
        RCLCPP_INFO(this->get_logger(),"node is activated");
    }
    private:
    void func(){
        auto msg = example_interfaces::msg::Int64();
        msg.data = 1;
        publisher ->publish(msg);
    }
    void number_callback(const example_interfaces::msg::Int64::SharedPtr msg){
        int num = msg->data;
        RCLCPP_INFO(this->get_logger(),"Number is : %d",num);  // Correct way
        // RCLCPP_INFO(this->get_logger(),"Number: %d",msg->data); Result in error message
    }
    void windSpeed_callback(const std_msgs::msg::Float32::SharedPtr msg){ // after creating a new subscription, if you use add a new dependency, rmb
                                                                            // to include it into executable, cmakelist , package.xml
        float data = msg->data;
        RCLCPP_INFO(this->get_logger(),"Wind speed is: %f",data);
    }

    rclcpp::TimerBase::SharedPtr timer_; 
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher;  
    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscriber;  
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr sub_wind;  

    int number;
    bool foo;
};

int main(int argc, char **argv){
    rclcpp::init(argc,argv);
    auto node = std::make_shared<NumberPublisher>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;

}
````
