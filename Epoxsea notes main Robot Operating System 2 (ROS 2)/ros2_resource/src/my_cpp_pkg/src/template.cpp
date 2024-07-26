#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"
class MyCustomNode: public rclcpp::Node
{
    public:
        MyCustomNode(): Node("MyCustomNode"),variable("type"){
        publisher = this->create_publisher<example_interfaces::msg::String>("topic",10);
        subscriber = this->create_subscription<example_interfaces::msg::String>("topic",10,
                                        std::bind(&MyCustomNode::sub_callback,this,std::placeholders::_1)); // placeholders = no. of parameters
        timer_ = this->create_wall_timer(std::chrono::milliseconds(500),     // set timer frequency
                                        std::bind(&MyCustomNode::func,this)); // call function
        RCLCPP_INFO(this->get_logger(),"node is activated");
    }
    private:
    void func(){
        auto msg = example_interfaces::msg::String();
        msg.data = std::string("blah blah blah");
        publisher ->publish(msg);
    }
    void sub_callback(const example_interfaces::msg::String::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(),"%s",msg->data.c_str());

    }
    rclcpp::TimerBase::SharedPtr timer_; 
    rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher;  
    rclcpp::Subscription<example_interfaces::msg::String>::SharedPtr subscriber;
    std::string variable;

};

int main(int argc, char **argv){
    rclcpp::init(argc,argv);
    auto node = std::make_shared<MyCustomNode>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;

}