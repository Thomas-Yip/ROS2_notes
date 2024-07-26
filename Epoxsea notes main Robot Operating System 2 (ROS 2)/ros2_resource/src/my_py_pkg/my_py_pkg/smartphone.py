#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import String

class smartphone(Node): #
    def __init__(self):
        super().__init__("smartphone")
        self.abd = self.create_subscription(String,"FM_98",self.callback_rthk,10)
        self.get_logger().info("smartphone node has been started")
        
    def callback_rthk(self,msg_1):
        self.get_logger().info(msg_1.data)
        
        
def main(args=None):
    rclpy.init()
    node = smartphone() #
    rclpy.spin(node)
    rclpy.shutdown()
if __name__ == "__main__":
    main()