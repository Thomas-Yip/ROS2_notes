#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import String

class RTHK(Node): #
    def __init__(self):
        super().__init__("RTHK")
        self.publisher=self.create_publisher(String,"FM_98",10)
        self.get_logger().info("Hello, you are listening to RTHK!")
        self.timer = self.create_timer(0.5,self.broadcast)
    def broadcast(self):
        msg_1 = String()
        msg_1.data = "No service"
        self.publisher.publish(msg_1)
        
        
def main(args=None):
    rclpy.init()
    node = RTHK() #
    rclpy.spin(node)
    rclpy.shutdown()
if __name__ == "__main__":
    main()

