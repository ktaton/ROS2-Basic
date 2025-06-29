cmake_minimum_required(VERSION 3.8)
project(topic_publisher_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(custom_interfaces REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

add_executable(simple_publisher_node src/simple_topic_publisher.cpp)
ament_target_dependencies(simple_publisher_node rclcpp std_msgs)

add_executable(move_robot_node src/move_robot.cpp)
ament_target_dependencies(move_robot_node rclcpp geometry_msgs)

add_executable(velocity_publisher_node src/velocity_publisher.cpp)
ament_target_dependencies(velocity_publisher_node rclcpp geometry_msgs)

install(TARGETS
   simple_publisher_node
   move_robot_node
   velocity_publisher_node
   DESTINATION lib/${PROJECT_NAME}
 )

# Install launch files.
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()