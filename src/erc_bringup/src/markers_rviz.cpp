#include "ros/ros.h"
#include "visualization_msgs/Marker.h"
#include "visualization_msgs/MarkerArray.h"
#include "nav_msgs/Odometry.h"


int main( int argc, char** argv )
{
  ros::init(argc, argv, "ERC_TD3");
  ros::NodeHandle n;
  ros::Rate r(1);
//   ros::Subscriber sub_path = n.subscribe("/odometry/filtered", 1, marker_callback);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::MarkerArray>("visualisation_markers", 1);
  ros::Publisher path_pub = n.advertise<visualization_msgs::MarkerArray>("real_path", 1);
 

  // Set our initial shape type to be a cube
   uint32_t shape = visualization_msgs::Marker::SPHERE;
  

  while (ros::ok())
  {
    visualization_msgs::MarkerArray marker_array_msg;

    // waypoint 1
    visualization_msgs::Marker marker1;
    marker1.header.frame_id = "map";
    marker1.header.stamp = ros::Time::now();
    marker1.ns = "goals";
    marker1.id = 0;
    marker1.type = shape;
    marker1.action = visualization_msgs::Marker::ADD;
    marker1.pose.position.x = 8.37;
    marker1.pose.position.y = -6.26;
    marker1.pose.position.z = 0.27157;
    marker1.pose.orientation.x = 0.0;
    marker1.pose.orientation.y = 0.0;
    marker1.pose.orientation.z = 0.0;
    marker1.pose.orientation.w = 1.0;
    marker1.scale.x = 0.25;
    marker1.scale.y = 0.25;
    marker1.scale.z = 0.25;
    marker1.color.r = 0.0f;
    marker1.color.g = 1.0f;
    marker1.color.b = 0.0f;
    marker1.color.a = 1.0;

    marker1.lifetime = ros::Duration();
    
    marker_array_msg.markers.push_back(marker1);

    // waypoint 2
    visualization_msgs::Marker marker2;
    marker2.header.frame_id = "map";
    marker2.header.stamp = ros::Time::now();
    marker2.ns = "goals";
    marker2.id = 1;
    marker2.type = shape;
    marker2.action = visualization_msgs::Marker::ADD;
    marker2.pose.position.x = 16.56;
    marker2.pose.position.y = 5.61;
    marker2.pose.position.z = 0.27137;
    marker2.pose.orientation.x = 0.0;
    marker2.pose.orientation.y = 0.0;
    marker2.pose.orientation.z = 0.0;
    marker2.pose.orientation.w = 1.0;
    marker2.scale.x = 0.25;
    marker2.scale.y = 0.25;
    marker2.scale.z = 0.25;
    marker2.color.r = 0.0f;
    marker2.color.g = 1.0f;
    marker2.color.b = 0.0f;
    marker2.color.a = 1.0;

    marker2.lifetime = ros::Duration();
    
    marker_array_msg.markers.push_back(marker2);

    // waypoint 3
    visualization_msgs::Marker marker3;
    marker3.header.frame_id = "map";
    marker3.header.stamp = ros::Time::now();
    marker3.ns = "goals";
    marker3.id = 2;
    marker3.type = shape;
    marker3.action = visualization_msgs::Marker::ADD;
    marker3.pose.position.x = 26.39;
    marker3.pose.position.y = 4.35;
    marker3.pose.position.z = 0.27174;
    marker3.pose.orientation.x = 0.0;
    marker3.pose.orientation.y = 0.0;
    marker3.pose.orientation.z = 0.0;
    marker3.pose.orientation.w = 1.0;
    marker3.scale.x = 0.25;
    marker3.scale.y = 0.25;
    marker3.scale.z = 0.25;
    marker3.color.r = 0.0f;
    marker3.color.g = 1.0f;
    marker3.color.b = 0.0f;
    marker3.color.a = 1.0;

    marker3.lifetime = ros::Duration();
    
    marker_array_msg.markers.push_back(marker3);

    // waypoint 4
    visualization_msgs::Marker marker4;
    marker4.header.frame_id = "map";
    marker4.header.stamp = ros::Time::now();
    marker4.ns = "goals";
    marker4.id = 3;
    marker4.type = shape;
    marker4.action = visualization_msgs::Marker::ADD;
    marker4.pose.position.x = 10.06;
    marker4.pose.position.y = -14.79;
    marker4.pose.position.z = 0.27244;
    marker4.pose.orientation.x = 0.0;
    marker4.pose.orientation.y = 0.0;
    marker4.pose.orientation.z = 0.0;
    marker4.pose.orientation.w = 1.0;
    marker4.scale.x = 0.25;
    marker4.scale.y = 0.25;
    marker4.scale.z = 0.25;
    marker4.color.r = 0.0f;
    marker4.color.g = 1.0f;
    marker4.color.b = 0.0f;
    marker4.color.a = 1.0;

    marker4.lifetime = ros::Duration();
    
    marker_array_msg.markers.push_back(marker4);

  //   // waypoint 5a
  //   visualization_msgs::Marker marker5a;
  //   marker5a.header.frame_id = "map";
  //   marker5a.header.stamp = ros::Time::now();
  //   marker5a.ns = "goals";
  //   marker5a.id = 4;
  //   marker5a.type = shape;
  //   marker5a.action = visualization_msgs::Marker::ADD;
  //   marker5a.pose.position.x = 7.64;
  //   marker5a.pose.position.y = -5.55;
  //   marker5a.pose.position.z = 0.27138;
  //   marker5a.pose.orientation.x = 0.0;
  //   marker5a.pose.orientation.y = 0.0;
  //   marker5a.pose.orientation.z = 0.0;
  //   marker5a.pose.orientation.w = 1.0;
  //   marker5a.scale.x = 0.25;
  //   marker5a.scale.y = 0.25;
  //   marker5a.scale.z = 0.25;
  //   marker5a.color.r = 1.0f;
  //   marker5a.color.g = 0.0f;
  //   marker5a.color.b = 1.0f;
  //   marker5a.color.a = 1.0;

  //   marker5a.lifetime = ros::Duration();
    
  //   marker_array_msg.markers.push_back(marker5a);

  //  // waypoint 5b
  //   visualization_msgs::Marker marker5b;
  //   marker5b.header.frame_id = "map";
  //   marker5b.header.stamp = ros::Time::now();
  //   marker5b.ns = "goals";
  //   marker5b.id = 5;
  //   marker5b.type = shape;
  //   marker5b.action = visualization_msgs::Marker::ADD;
  //   marker5b.pose.position.x = 27.48;
  //   marker5b.pose.position.y = -13.65;
  //   marker5b.pose.position.z = 0.27146;
  //   marker5b.pose.orientation.x = 0.0;
  //   marker5b.pose.orientation.y = 0.0;
  //   marker5b.pose.orientation.z = 0.0;
  //   marker5b.pose.orientation.w = 1.0;
  //   marker5b.scale.x = 0.25;
  //   marker5b.scale.y = 0.25;
  //   marker5b.scale.z = 0.25;
  //   marker5b.color.r = 1.0f;
  //   marker5b.color.g = 0.0f;
  //   marker5b.color.b = 1.0f;
  //   marker5b.color.a = 1.0;

  //   marker5b.lifetime = ros::Duration();
    
  //   marker_array_msg.markers.push_back(marker5b);

// Publish the marker array
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    marker_pub.publish(marker_array_msg);

    r.sleep();
  }
}


