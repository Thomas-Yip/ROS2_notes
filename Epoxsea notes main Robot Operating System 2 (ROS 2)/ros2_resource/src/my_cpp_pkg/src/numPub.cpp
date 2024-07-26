#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"
class NumberPublisher: public rclcpp::Node
{
    public:
        NumberPublisher(): Node("NumberPublisher"),number(64){
        this->declare_parameter("number",2);
        number = this->get_parameter("number").as_int();
        publisher = this->create_publisher<example_interfaces::msg::Int64>("number",10);
    
        timer_ = this->create_wall_timer(std::chrono::seconds(1),     // set timer frequency
                                        std::bind(&NumberPublisher::func,this)); // call function
        RCLCPP_INFO(this->get_logger(),"node is activated");
    }
    private:
    void func(){
        auto msg = example_interfaces::msg::Int64();
        msg.data = std::int64_t(number);
        publisher ->publish(msg);
    }
    std::vector<int64_t> led_states_;

    rclcpp::TimerBase::SharedPtr timer_; 
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher;  
    std::int64_t number;

};

int main(int argc, char **argv){
    rclcpp::init(argc,argv);
    auto node = std::make_shared<NumberPublisher>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;

}