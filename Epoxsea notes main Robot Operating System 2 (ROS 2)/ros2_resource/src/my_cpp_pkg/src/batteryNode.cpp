#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"
#include "my_robot_interfaces/srv/led_status.hpp"
#include "my_robot_interfaces/msg/battery_status.hpp"
// ros2 interface show example_interfaces/srv/AddTwoInts
class battery: public rclcpp::Node
{
    public:
        battery(): Node("battery"),local_batteryfull(),local_lednum(){
        timer = this->create_wall_timer(std::chrono::seconds(1),std::bind(&battery::setLed,this));
        subscriber = this->create_subscription<my_robot_interfaces::msg::BatteryStatus>("battery_status",10,
                                        std::bind(&battery::subCallback,this,std::placeholders::_1)); // placeholders = no. of parameters
        }
    void setLed(){
        threads_.push_back(std::thread(std::bind(&battery::batteryStatus,this)));

    }
    void batteryStatus(){
      auto client = this->create_client<my_robot_interfaces::srv::LedStatus>("LedStatus");
      while (!client->wait_for_service(std::chrono::seconds(1))){
        RCLCPP_WARN(this->get_logger(),"Waiting the server to be up");
      }
        auto request = std::make_shared<my_robot_interfaces::srv::LedStatus::Request>();
        request->batteryfull = local_batteryfull;
        request->lednum = local_lednum;
        auto future = client->async_send_request(request);
        try{
            auto response = future.get();
            RCLCPP_INFO(this->get_logger(),"lednum:%d,batteryfull:%d:%d",request->lednum,request->batteryfull);
        }catch(const std::exception &e){
            RCLCPP_ERROR(this->get_logger(),"service call failed");
    }
    }
    void subCallback(const my_robot_interfaces::msg::BatteryStatus::SharedPtr msg){
        local_batteryfull = msg->batteryfull;
        local_lednum = msg->lednum;
        // RCLCPP_INFO(this->get_logger(),"batteryfull:%d,lednum:%d",msg->batteryfull,msg->lednum);
    }
    private:

        rclcpp::Subscription<my_robot_interfaces::msg::BatteryStatus>::SharedPtr subscriber;
        std::int8_t local_lednum;
        std::int8_t local_batteryfull;
        std::vector<std::thread>threads_;
        rclcpp::TimerBase::SharedPtr timer;






};

int main(int argc, char **argv){
    rclcpp::init(argc,argv);
    auto node = std::make_shared<battery>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;

}