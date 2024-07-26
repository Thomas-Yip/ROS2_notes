# Create a server

## 1. Create placeholders

````cpp
using std::placeholders::_1;
````

In the callback function, since there are two parameters, so we need to placeholders.

## 2. Create service provider

````cpp
server = this->create_service<Interface_name::srv::Service_name>("Service_name",
std::bind(&Service_name::callback_func,this,_1,_2));      
````

Under private, add

````cpp
rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr server;

````

## 3. Create callback function

````cpp
void callbackAddTwoInts(const example_interfaces::srv::AddTwoInts::Request::SharedPtr request
                            ,const example_interfaces::srv::AddTwoInts::Response::SharedPtr response)
    {
        response->sum = request->a + request->b;
        RCLCPP_INFO(this->get_logger(),"%d + %d = %d",request->a,request->b,response->sum);
    }
````

example

````cpp
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"
using std::placeholders::_1;
using std::placeholders::_2;
class AddTwoIntsServerNode: public rclcpp::Node
{   
    public:
        AddTwoIntsServerNode(): Node("AddTwoIntsServerNode"){
        server = this->create_service<example_interfaces::srv::AddTwoInts>("AddTwoInts",
        std::bind(&AddTwoIntsServerNode::callbackAddTwoInts,this,_1,_2));        
        RCLCPP_INFO(this->get_logger(),"node is activated");
    }
    private:
    void callbackAddTwoInts(const example_interfaces::srv::AddTwoInts::Request::SharedPtr request
                            ,const example_interfaces::srv::AddTwoInts::Response::SharedPtr response)
    {
        response->sum = request->a + request->b;
        RCLCPP_INFO(this->get_logger(),"%d + %d = %d",request->a,request->b,response->sum);
    }
    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr server;
};

````
