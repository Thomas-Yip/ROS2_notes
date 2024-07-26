#!/usr/bin/env python3
import rclpy
import random
from rclpy.node import Node
from example_interfaces.msg import String
from example_interfaces.msg import Int64

class pub_num(Node): #
    def __init__(self):
        super().__init__("number_publisher")
        self.declare_parameter("test123")
        self.publisher = self.create_publisher(Int64,"number",10)
        self.get_logger().info("number_pusblisher starts broadcasting")
        self.timer = self.create_timer(1,self.broadcast_msg)
    def broadcast_msg(self):
        msg = Int64()
        if (random.choice([0,1])==1):
            msg.data = 64
        else:
            msg.data = 78
        self.publisher.publish(msg)
def main(args=None):
    rclpy.init()
    node = pub_num() #
    rclpy.spin(node)
    rclpy.shutdown()
if __name__ == "__main__":
    main()