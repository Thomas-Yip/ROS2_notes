#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"
#include "my_robot_interfaces/srv/led_status.hpp"
using std::placeholders::_1;
using std::placeholders::_2;
class led: public rclcpp::Node
{   
    public:
        led(): Node("led"),pubPanel("00000"),change("0"){
        server = this->create_service<my_robot_interfaces::srv::LedStatus>("LedStatus",
        std::bind(&led::callback_led,this,_1,_2));  
        ledPublisher = this->create_publisher<example_interfaces::msg::String>("led_states",10);
        timer = this->create_wall_timer(std::chrono::seconds(1),std::bind(&led::led_status,this));
        
        RCLCPP_INFO(this->get_logger(),"node is activated");
    }
    private:
    void callback_led(const my_robot_interfaces::srv::LedStatus::Request::SharedPtr request
                            ,const my_robot_interfaces::srv::LedStatus::Response::SharedPtr response)
    {   
        int led_panel[4] = {0,0,0};
        if(request->batteryfull){
            led_panel[request->lednum] = 0;
        }else{
            led_panel[request->lednum] = 1;
        }
        for (int i = 0;i < 3;i++){
            char temp = led_panel[i]+'0';
            pubPanel[i*2] = temp;
            if(i!=2)
                pubPanel[i*2+1] = ',';
            }
        response->successful = true;
        RCLCPP_INFO(this->get_logger(),"successful:%d",response->successful);
        
    }
    void led_status(){
        
        auto msg = example_interfaces::msg::String();
        msg.data = std::string(pubPanel);
        ledPublisher ->publish(msg);
    }
    rclcpp::Service<my_robot_interfaces::srv::LedStatus>::SharedPtr server;
    rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr ledPublisher;
    rclcpp::TimerBase::SharedPtr timer; 
    std::string pubPanel;
    std::string change;
};

int main(int argc, char **argv){
    rclcpp::init(argc,argv);
    auto node = std::make_shared<led>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;

}