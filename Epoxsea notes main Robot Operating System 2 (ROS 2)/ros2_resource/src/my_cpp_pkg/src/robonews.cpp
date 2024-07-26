#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"
// ros2 service call /SetBool example_interfaces/srv/SetBool "{data: true}"
class robonews: public rclcpp::Node
{
    public:
        robonews(): Node("robonews"), robot_name("R2D2")
        {   this->declare_parameter("name","");
            robot_name = this->get_parameter("name").as_string();
            publisher_ = this->create_publisher<example_interfaces::msg::String>("robot_news",10); // create publisher "publisher_", topic is robot_news
            timer_ = this->create_wall_timer(std::chrono::milliseconds(500),     // set timer frequency
                                            std::bind(&robonews::publishNews,this) // call function
            );
            RCLCPP_INFO(this->get_logger(),"Robot news station has started"); // print msg in terminal
        }
    private:
        void publishNews()
        {
            auto msg = example_interfaces::msg::String(); // specify msg type
            msg.data = std::string("Hello world! This is robot news! I am ")+robot_name; // create a msg
            publisher_ ->publish(msg); // publisher_ publish msg
        }
        rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher_;  
        rclcpp::TimerBase::SharedPtr timer_; 
        std::string robot_name;
};

int main(int argc, char **argv){
    rclcpp::init(argc,argv);
    auto node = std::make_shared<robonews>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;

}