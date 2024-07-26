#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts
class add_two_ints_server(Node): #
    def __init__(self):
        super().__init__("add_two_ints_server_node")
        self.server = self.create_service(AddTwoInts,"add_two_ints",self.callback_add_two_ints)
        self.get_logger().info("add_two_ints_server_node_starts")
    def callback_add_two_ints(self,request,response):
        response.sum = request.a+request.b
        self.get_logger().info(str(request.a)+"+"+str(request.b)+"="+str(response.sum))
        return response
def main(args=None):
    rclpy.init()
    node = add_two_ints_server() #
    rclpy.spin(node)
    rclpy.shutdown()
if __name__ == "__main__":
    main()