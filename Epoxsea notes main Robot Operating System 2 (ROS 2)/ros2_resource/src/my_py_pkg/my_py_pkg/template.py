#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
class custom_node(Node): #
    def __init__(self):
        super().__init__("name") # create a node
        self.get_logger().info("first_msg") # print message
def main(args=None):
    rclpy.init()
    node = custom_node() #
    rclpy.spin(node)
    rclpy.shutdown()
if __name__ == "__main__":
    main()