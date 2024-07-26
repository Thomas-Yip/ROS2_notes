#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from my_robot_interfaces.srv import LedStatus # custom message
from functools import partial # important for OOP
import time
class battery(Node): #
    def __init__(self):
        super().__init__("battery_client") # create a node
        self.get_logger().info("activated") # print message
        batteryfull = True
        lednum = 0
        Toggle = True
        while(True):
            self.call_led_server(lednum,batteryfull) # call server function
            if(Toggle):
                time.sleep(4)
                batteryfull = False
                lednum = 3
                Toggle = False
            else:
                time.sleep(6)
                batteryfull = True
                lednum = 3
                Toggle = True
    def call_led_server(self,lednum,batteryfull):
        client = self.create_client(LedStatus,"set_led") # create client
        while not client.wait_for_service(1.0):
            self.get_logger().warn("Waiting for server ")
        request = LedStatus.Request()
        request.lednum = lednum
        request.batteryfull = batteryfull
        
        future = client.call_async(request)
        future.add_done_callback(partial(self.callback_call_ledstatus,lednum=lednum,batteryfull=batteryfull))
        
    def callback_call_ledstatus(self,future,lednum,batteryfull):
        try:
            response = future.result()
            self.get_logger().info(response.successful)
        except Exception as e:
            self.get_logger().error("serice called fail")
               
def main(args=None):
    rclpy.init()
    node = battery() #
    rclpy.spin(node)
    rclpy.shutdown()
if __name__ == "__main__":
    main()