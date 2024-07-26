#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import String

class custom_node(Node): # create a node, name it by yourself
    def __init__(self):
        super().__init__("name") # node name
        self.publisher = self.create_publisher(String,"Topic name",10) # create a publsiher + fill in parameters
        self.get_logger().info("first_msg") # print sth to indicate the node is activated
        self.timer = self.create_timer(1.0,self.broadcast_msg) # call function self.broadcast.msg every ?seconds
    def broadcast_msg(self): # name the callback function by yourself
        msg = String() # what kind of data type you want to publish
        msg.data = "Publish a message" # what you want to publish
        self.publisher.publish(msg) # publish message
def main(args=None):
    rclpy.init()
    node = custom_node() #
    rclpy.spin(node) #  while loop
    rclpy.shutdown()
if __name__ == "__main__":
    main()