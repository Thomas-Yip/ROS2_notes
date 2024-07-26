#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"
#include "example_interfaces/msg/string.hpp"
#include "example_interfaces/srv/set_bool.hpp"
using std::placeholders::_1;
using std::placeholders::_2;

class numberSubscriber: public rclcpp::Node
{
    public:
        numberSubscriber(): Node("numberSubscriber"),numCount(0){
        server = this->create_service<example_interfaces::srv::SetBool>("SetBool",
                std::bind(&numberSubscriber::reset,this,_1,_2));        
        publisher = this->create_publisher<example_interfaces::msg::Int64>("number_count",10);
        subscriber = this->create_subscription<example_interfaces::msg::Int64>("number",10,
                                        std::bind(&numberSubscriber::sub_callback,this,std::placeholders::_1)); // placeholders = no. of parameters
        timer_ = this->create_wall_timer(std::chrono::seconds(1),     // set timer frequency
                                        std::bind(&numberSubscriber::func,this)); // call function
        RCLCPP_INFO(this->get_logger(),"node is activated");
    }
    private:
    void func(){
        auto msg1 = example_interfaces::msg::Int64();
        msg1.data = numCount;
        publisher ->publish(msg1);
    }
    void sub_callback(const example_interfaces::msg::Int64::SharedPtr msg)
    {   if (msg->data == 64){
        numCount += 1;
    }
    }
    void reset(const example_interfaces::srv::SetBool::Request::SharedPtr request
                            ,const example_interfaces::srv::SetBool::Response::SharedPtr response)
    {
        if (request->data ){
            numCount = 0;
            response->success = true;
            response->message = "reset successful";
        }else{
            response->success = false;
            response->message = "reset failed";
        }
        RCLCPP_INFO(this->get_logger(),"%d",response->success);
    }
    rclcpp::TimerBase::SharedPtr timer_; 
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher;  
    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscriber;
    rclcpp::Service<example_interfaces::srv::SetBool>::SharedPtr server;

    std::int64_t numCount;

};

int main(int argc, char **argv){
    rclcpp::init(argc,argv);
    auto node = std::make_shared<numberSubscriber>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;

}