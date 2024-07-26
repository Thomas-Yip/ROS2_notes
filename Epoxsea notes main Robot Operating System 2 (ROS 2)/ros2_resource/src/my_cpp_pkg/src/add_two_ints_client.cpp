#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"
// ros2 interface show example_interfaces/srv/AddTwoInts
class AddTwoIntsClient: public rclcpp::Node
{
    public:
        AddTwoIntsClient(): Node("AddTwoIntsClient"){
        thread_1 = std::thread(std::bind(&AddTwoIntsClient::AddTwoIntsService,this,1,4));

        }
    void AddTwoIntsService(int a, int b){
      auto client = this->create_client<example_interfaces::srv::AddTwoInts>("AddTwoInts");
      while (!client->wait_for_service(std::chrono::seconds(1))){
        RCLCPP_WARN(this->get_logger(),"Waiting the server to be up");
      }
        auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
        request->a = a;
        request->b = b;
        auto future = client->async_send_request(request);
        try{
            auto response = future.get();
            RCLCPP_INFO(this->get_logger(),"%d + %d = %d",request->a,request->b,response->sum);
        }catch(const std::exception &e){
            RCLCPP_ERROR(this->get_logger(),"service call failed");
        }
    }
    private:
        std::thread thread_1;


};

int main(int argc, char **argv){
    rclcpp::init(argc,argv);
    auto node = std::make_shared<AddTwoIntsClient>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;

}