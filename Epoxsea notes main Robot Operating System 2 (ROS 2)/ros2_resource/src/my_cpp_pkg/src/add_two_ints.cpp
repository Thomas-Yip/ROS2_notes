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

int main(int argc, char **argv){
    rclcpp::init(argc,argv);
    auto node = std::make_shared<AddTwoIntsServerNode>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;

}