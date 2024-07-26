#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"
#include "turtlesim/srv/kill.hpp"
#include "turtlesim/srv/set_pen.hpp"
#include "turtlesim/srv/spawn.hpp"
#include "std_msgs/msg/int16_multi_array.hpp"
#define pi 3.141
// ros2 interface show example_interfaces/srv/AddTwoInts
class Server: public rclcpp::Node
{
    public:
        Server(): Node("Server"),num(1),global_turtle_x(),global_turtle_y(){
        timer = this->create_wall_timer(std::chrono::seconds(1),std::bind(&Server::birth,this));
        coor_publisher = this->create_publisher<std_msgs::msg::Int16MultiArray>("turtle_coor",10);
        }
    void turtle_coor(){
        auto msg = std_msgs::msg::Int16MultiArray();
        msg.data = {global_turtle_x,global_turtle_y,num};
        coor_publisher ->publish(msg);
    }
    
    void birth(){
        threads_.push_back(std::thread(std::bind(&Server::spawn,this)));

    }
    void spawn(){
      auto client = this->create_client<turtlesim::srv::Spawn>("spawn");
      while (!client->wait_for_service(std::chrono::seconds(1))){
        RCLCPP_WARN(this->get_logger(),"Waiting the server to be up");
      }
        auto request = std::make_shared<turtlesim::srv::Spawn::Request>();
        request->x = rand()% 11+0;
        request->y = rand()% 11+0;
        global_turtle_x = request->x;
        global_turtle_y = request->y;
        request->theta = rand()% 3+-3;
        num+=1;
        std::string temp = std::to_string(num);
        request->name = "turtle"+temp;
        auto future = client->async_send_request(request);
        try{
            auto response = future.get();
            RCLCPP_INFO(this->get_logger(),"x:%f,y:%f",request->x,request->y);
        }catch(const std::exception &e){
            RCLCPP_ERROR(this->get_logger(),"service call failed");
    }
        turtle_coor();
    }
    private:
        rclcpp::Publisher<std_msgs::msg::Int16MultiArray>::SharedPtr coor_publisher;
        std::vector<std::thread>threads_;
        rclcpp::TimerBase::SharedPtr timer;
        rclcpp::TimerBase::SharedPtr timer1;
        std::int8_t global_turtle_x;
        std::int8_t global_turtle_y;
        std::int8_t num;
};

int main(int argc, char **argv){
    rclcpp::init(argc,argv);
    auto node = std::make_shared<Server>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;

}
