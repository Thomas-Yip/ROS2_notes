#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.srv import SetBool
def main(args=None): # client no OOP
    rclpy.init(args = args)
    node = Node("reset_counter_client_no_oop") # node name
    client = node.create_client(SetBool,"number_counter_reset") # choose service type, name of client
    
    while not client.wait_for_service(1.0):
        node.get_logger().warn("Wait for server number counter")
        
    request= SetBool.Request() # choose service type
    request.data = True
    future = client.call_async(request)
    rclpy.spin_until_future_complete(node,future)
    try:
        response = future.result()
        node.get_logger().info(str(request))

    except Exception as e:
        node.get_logger().error("service call failed")
    rclpy.shutdown()
if __name__ == "__main__":
    main()