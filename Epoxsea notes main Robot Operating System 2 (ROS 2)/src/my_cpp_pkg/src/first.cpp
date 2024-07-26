#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

class numberPublisher: public rclcpp::Node
{
    public:
        numberPublisher(): Node("numberPublisher"){
        publisher = this->create_publisher<example_interfaces::msg::Int64>("number",10); // interface, topic name, qos
        timer_ = this->create_wall_timer(std::chrono::seconds(1),     // set timer frequency
                                        std::bind(&numberPublisher::foo,this)); // call function (func)
        // subscriber = this->create_subscription<example_interfaces::msg::Int64>("number",10, std::bind(&numberPublisher::bar,this,std::placeholders::_1));  // inteface, topic name, qos (usually 10 + idk the meaning), callback function)

        }
    private:
        void foo(){
            auto msg = example_interfaces::msg::Int64(); // decide the interface of the msg
            int a = 123;
            msg.data = a;
            publisher->publish(msg);
        }
    //     void bar(const example_interfaces::msg::Int64::SharedPtr msg){
    //         RCLCPP_INFO(this->get_logger(),"%d",msg->data);
    //    }
            rclcpp::TimerBase::SharedPtr timer_; 
            rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher;
            // rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscriber;
 

};
int main(int argc, char **argv){
    rclcpp::init(argc,argv);
    auto node = std::make_shared<numberPublisher>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;

}