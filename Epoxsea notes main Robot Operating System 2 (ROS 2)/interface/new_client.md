### Example

````cpp
/*
This is the client side matrix service.
When you want to tune the vector of the thrusters, use $ ros2 run rov_control matrixClient X Y Z
X -> motion
Y -> number of the thruster
Z -> new value
Valid range of X , Y , Z
X: [ 1 , 8 ]
Y: [ 1 , 8 ]
Z: [ 9.99999, -9.99999 ]
Since the values are stored in matrix.txt, it saves the time to rebuild the program.
*/
#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/srv/matrix_service.hpp"                                       // CHANGE
#include <chrono>
#include <cstdlib>
#include <memory>
using namespace std::chrono_literals;
int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  if (argc != 4) { // CHANGE
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "usage: matrix_service_client X Y Z");      // CHANGE
      return 1;
  }
  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("client");  // CHANGE name of the client side
  rclcpp::Client<custom_interfaces::srv::MatrixService>::SharedPtr client =                // CHANGE
    node->create_client<custom_interfaces::srv::MatrixService>("matrixService");          // CHANGE name of the service that the client is calling

  auto request = std::make_shared<custom_interfaces::srv::MatrixService::Request>();       // calling the service 
// filling the necessary information when requesting a service
    request->motion = atoi(argv[1]);    
    request->thruster_name = atoi(argv[2]);
    request->new_value = atof(argv[3]);                                                           

  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }
  auto result = client->async_send_request(request); 
  // Wait for the result.
  if (rclcpp::spin_until_future_complete(node, result) ==
    rclcpp::FutureReturnCode::SUCCESS)
  { 
    if(result.get()->success)
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "value is changed successfully !");
    else
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "value is not changed :("); 
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service matrixService");    // CHANGE
  }
  rclcpp::shutdown();
  return 0;
}
````
