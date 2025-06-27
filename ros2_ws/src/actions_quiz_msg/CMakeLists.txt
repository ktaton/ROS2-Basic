cmake_minimum_required(VERSION 3.8)
project(actions_quiz_msg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Required dependencies
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# Interface generation
rosidl_generate_interfaces(${PROJECT_NAME}
  "action/Distance.action"
  DEPENDENCIES builtin_interfaces
)

# Export dependencies
ament_export_dependencies(rosidl_default_runtime)

# Enable testing and linting (optional)
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# Call ament_package LAST
ament_package()
