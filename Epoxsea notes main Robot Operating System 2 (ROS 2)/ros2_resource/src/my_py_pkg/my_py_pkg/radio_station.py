#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import String

class radio_station(Node):
    def __init__(self):
        super().__init__("robot_news_station")
        self.publisher_=self.create_publisher(String,"robot_news",10)
        self.get_logger().info("news_station starts")
        self.timer = self.create_timer(1,self.publish_news)
    def publish_news(self):
        msg_1 = String()
        msg_1.data = "Hello"
        self.publisher_.publish(msg_1)
def main(args=None):
    rclpy.init()
    node = radio_station()
    rclpy.spin(node)
    rclpy.shutdown()
if __name__ == "__main__":
    main()
