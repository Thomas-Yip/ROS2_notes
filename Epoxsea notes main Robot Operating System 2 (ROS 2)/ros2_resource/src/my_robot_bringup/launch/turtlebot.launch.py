from launch import LaunchDescription
from launch_ros.actions import Node
def generate_launch_description():
    ld = LaunchDescription()
    control_node = Node(
        package = "turtlebot",
        executable = "     " // Your executable 
    )
    server_node = Node(
        package = "turtlebot",
        executable = "server"
    )
    
    ld.add_action(control_node)
    ld.add_action(server_node)
    
    return ld
