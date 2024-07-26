#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import Int64
from my_robot_interfaces.msg import HardwareStatus

class hw_status_publisher(Node): #
    def __init__(self):
        super().__init__("hw_status_publisher") # create a node
        self.hw_status_publisher = self.create_publisher(HardwareStatus,"hardware_status",10)
        self.timer = self.create_timer(1.0,self.publish_hw_status)
        self.get_logger().info("hardware status publisher has been started") # print message

    def publish_hw_status(self):
        msg = HardwareStatus()
        msg.temperature = 45
        msg.are_motors_ready = True
        msg.debug_message = "Nothing special here"
        self.hw_status_publisher.publish(msg)
def main(args=None):
    rclpy.init()
    node = hw_status_publisher() #
    rclpy.spin(node)
    rclpy.shutdown()
if __name__ == "__main__":
    main()