cmake_minimum_required(VERSION 3.8)
project(my_cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED) # edited
find_package(my_robot_interfaces REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

#edited
# add executable
add_executable(MyCustomNode src/template.cpp)
ament_target_dependencies(MyCustomNode rclcpp example_interfaces)
add_executable(numPub src/numPub.cpp)
ament_target_dependencies(numPub rclcpp example_interfaces)
add_executable(numSub src/numSub.cpp)
ament_target_dependencies(numSub rclcpp example_interfaces)
add_executable(batteryNode src/batteryNode.cpp)
ament_target_dependencies(batteryNode rclcpp example_interfaces my_robot_interfaces)
add_executable(led_node src/led.cpp)
ament_target_dependencies(led_node rclcpp example_interfaces my_robot_interfaces)
add_executable(batteryPub src/batteryPub.cpp)
ament_target_dependencies(batteryPub rclcpp example_interfaces my_robot_interfaces)
# add executable

install(TARGETS # install executable into the workspace

  MyCustomNode
  numPub
  numSub
  batteryNode
  led_node
  batteryPub
  DESTINATION lib/${PROJECT_NAME}

)
#edited
ament_package()
