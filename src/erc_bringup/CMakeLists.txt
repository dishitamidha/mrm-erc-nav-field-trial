cmake_minimum_required(VERSION 3.0.2)

project(erc_bringup)

find_package(catkin REQUIRED COMPONENTS
actionlib
move_base_msgs
roscpp
rospy
ar_track_alvar
pcl_ros
pcl_conversions
)
include_directories(include ${catkin_INCLUDE_DIRS})

catkin_package()

install(
  DIRECTORY
    launch
    config
    src
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

catkin_install_python(
  PROGRAMS 
    scripts/image_saver
    scripts/path.py
    scripts/pdu_node
    scripts/waypoint_probe_deployment.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

add_executable(wheel_pose_republish src/wheel_pose_repub.cpp)
target_link_libraries(wheel_pose_republish ${catkin_LIBRARIES})
add_dependencies(wheel_pose_republish ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(wheel_twist_republish src/wheel_twist_repub.cpp)
target_link_libraries(wheel_twist_republish ${catkin_LIBRARIES})
add_dependencies(wheel_twist_republish ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(ar2 src/ar2.cpp)
target_link_libraries(ar2 ${catkin_LIBRARIES})
add_dependencies(ar2 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(markers_rviz src/markers_rviz.cpp)
target_link_libraries(markers_rviz ${catkin_LIBRARIES})
add_dependencies(markers_rviz ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(sub_marker src/sub_marker.cpp)
target_link_libraries(sub_marker ${catkin_LIBRARIES})
add_dependencies(sub_marker ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(Cancel src/Cancel.cpp)
target_link_libraries(Cancel ${catkin_LIBRARIES})
add_dependencies(Cancel ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(goal_setting src/goal.cpp)
target_link_libraries(goal_setting ${catkin_LIBRARIES})
add_dependencies(goal_setting ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(stopper src/stop.cpp)
target_link_libraries(stopper ${catkin_LIBRARIES})
add_dependencies(stopper ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})