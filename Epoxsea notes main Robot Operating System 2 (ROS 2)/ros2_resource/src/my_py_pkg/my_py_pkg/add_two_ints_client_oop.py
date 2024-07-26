#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts
from functools import partial
import time
import random
class custom_node(Node): #
    def __init__(self):
        super().__init__("add_two_ints_client") # create a node
        self.get_logger().info("first_msg") # print message
        while(True):
            self.call_add_two_ints_server(random.randint(1,100),random.randint(1,100))
            time.sleep(1)
        
    def call_add_two_ints_server(self,a,b):
        client = self.create_client(AddTwoInts,"add_two_ints")
        while not client.wait_for_service(1.0):
            self.get_logger().warn("Waiting for server ")
        request = AddTwoInts.Request()
        request.a = a
        request.b = b
        
        future = client.call_async(request)
        future.add_done_callback(partial(self.callback_call_add_two_ints,a=a,b=b))
        
    def callback_call_add_two_ints(self,future,a,b):
        try:
            response = future.result()
            self.get_logger().info(str(a)+"+"+str(b)+"="+str(response.sum))
        except Exception as e:
            self.get_logger().error("serice called fail")
               
def main(args=None):
    rclpy.init()
    node = custom_node() #
    rclpy.spin(node)
    rclpy.shutdown()
if __name__ == "__main__":
    main()