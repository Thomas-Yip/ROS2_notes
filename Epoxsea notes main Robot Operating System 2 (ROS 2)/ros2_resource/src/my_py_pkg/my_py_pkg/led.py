#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from my_robot_interfaces.srv import LedStatus 
from example_interfaces.msg import String
import time
class led(Node): #
    def __init__(self):
        super().__init__("led_panel") # create a node
        self.get_logger().info("led server activated") # show the node is activated
        self.led2 = [0,0,0]
        server = self.create_service(LedStatus,"set_led",self.callback_set_led) # important for server
        self.publisher = self.create_publisher(String,"led_states",10) # create publisher to publish led state
        self.timer = self.create_timer(1.0,self.callback_publish) # publish led state
        
    def callback_set_led(self,request,response):
        if (request.batteryfull == False):
            self.led2[request.lednum-1] = 1
            response.successful = True 
            return response 
        else:
            self.led2[request.lednum-1] = 0
            response.successful = True
            return response
    
    def callback_publish(self):
        msg = String() # msg type
        msg.data = str(self.led2) # assign info to the msg
        self.publisher.publish(msg)
            
        
        
def main(args=None):
    rclpy.init()
    node = led() #
    rclpy.spin(node)
    rclpy.shutdown()
if __name__ == "__main__":
    main()
