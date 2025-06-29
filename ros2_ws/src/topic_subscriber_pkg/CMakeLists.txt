cmake_minimum_required(VERSION 3.8)
project(topic_subscriber_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)

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

add_executable(simple_subscriber_node src/simple_topic_subscriber.cpp)
add_executable(sub_odom_node src/sub_odom.cpp)
ament_target_dependencies(simple_subscriber_node rclcpp std_msgs)
ament_target_dependencies(sub_odom_node rclcpp std_msgs nav_msgs)

add_executable(laser_subscriber_node src/laser_subscriber.cpp)
ament_target_dependencies(laser_subscriber_node rclcpp sensor_msgs geometry_msgs)

install(TARGETS
   simple_subscriber_node
   sub_odom_node
   laser_subscriber_node
   DESTINATION lib/${PROJECT_NAME}
 )

# Install launch files.
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()
