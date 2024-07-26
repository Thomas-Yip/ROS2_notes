#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"
#include "my_robot_interfaces/msg/battery_status.hpp"
#include <ctime>
#include <unistd.h>

class batteryPub: public rclcpp::Node
{
    public:
        batteryPub(): Node("batteryPub"),toggle(1){
        last_tick = this->get_clock()->now().seconds();
        publisher = this->create_publisher<my_robot_interfaces::msg::BatteryStatus>("battery_status",10);
        timer_ = this->create_wall_timer(std::chrono::seconds(1),     // set timer frequency
                                        std::bind(&batteryPub::func,this)); // call function
        RCLCPP_INFO(this->get_logger(),"batteryPub is activated");
    }
    private:
    void func(){
        auto msg = my_robot_interfaces::msg::BatteryStatus();
        int64_t time_now = this->get_clock()->now().seconds();

        if(toggle == 1){
            if (time_now-last_tick >= 4){
                toggle = 0;
                last_tick = time_now;
                local_batteryfull = 0;
                RCLCPP_INFO(this->get_logger(),"hi");
            }
        }else if(toggle == 0){
            if(time_now-last_tick >=6){
                toggle = 1;
                last_tick = time_now;
                local_batteryfull = 1;
                RCLCPP_INFO(this->get_logger(),"bye");
            }
        }
        RCLCPP_INFO(this->get_logger(),"%d",toggle);
        msg.lednum = 2;
        msg.batteryfull = local_batteryfull;
        publisher ->publish(msg);
    }
    
    rclcpp::TimerBase::SharedPtr timer_; 
    rclcpp::Publisher<my_robot_interfaces::msg::BatteryStatus>::SharedPtr publisher;  
    std::int8_t toggle;
    std::int8_t lock;
    int64_t last_tick;
    int8_t local_batteryfull;

};

int main(int argc, char **argv){
    rclcpp::init(argc,argv);
    auto node = std::make_shared<batteryPub>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;

}