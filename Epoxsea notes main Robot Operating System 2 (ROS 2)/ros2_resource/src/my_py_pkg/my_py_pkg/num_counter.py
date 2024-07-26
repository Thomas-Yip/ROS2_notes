#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import Int64
from example_interfaces.srv import SetBool
counter_machine = 0
class number_counter(Node): # a node can contain several subscriber, server ..........
    counter_machine = 0
    def __init__(self):
        super().__init__("smartphone")
        self.get_logger().info("number counter node has been started")
        self.abd = self.create_subscription(Int64,"number",self.counter,10)
        self.server = self.create_service(SetBool,"number_counter_reset",self.counter_reset)
        self.publisher = self.create_publisher(Int64,"number_count",10)
        
    def counter(self,msg):
        global counter_machine
        if (msg.data == 64):
            counter_machine += 1
        else:
            counter_machine -= 1
   
        msg1 = Int64() # create another msg, the name should be consistent for publisher and subscribers
        msg1.data = counter_machine
        self.publisher.publish(msg1)
    def counter_reset(self,request,response):
        global counter_machine
        if request.data == True:
            counter_machine = 0
            response.success = True
        if response.success:
            response.message = "Reset successful"
            return response
        

        
        
def main(args=None):
    rclpy.init()
    node = number_counter() #
    rclpy.spin(node)
    rclpy.shutdown()
if __name__ == "__main__":
    main()