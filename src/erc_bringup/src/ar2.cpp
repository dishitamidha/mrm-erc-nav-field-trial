#include "ros/ros.h"
#include "ar_track_alvar_msgs/AlvarMarkers.h"
#include "ar_track_alvar_msgs/AlvarMarker.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseWithCovariance.h"
#include "geometry_msgs/TwistWithCovarianceStamped.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/TwistWithCovariance.h"
#include "sensor_msgs/Imu.h"
#include "nav_msgs/Odometry.h"
#include <math.h>
#include <iostream>
#include <string>
int counter = 0; //


class ar
{
        private:
            // sdjdkhf
            ros::Publisher pub;
            ros::Publisher pub_odom;
            ros::Subscriber sub;
            ros::Subscriber sub_imu;
            ros::Subscriber sub_twist;
            ros::Subscriber sub_odom;
            ros::Subscriber sub_pose;
            sensor_msgs::Imu orientation_imu;
            geometry_msgs::TwistWithCovariance vel;
            geometry_msgs::PoseStamped pose_header;
            nav_msgs::Odometry odom;
            
            // this avriabke we..
            nav_msgs::Odometry ar_odom_local;


    public:
    inline ar(ros::NodeHandle *n)
    {
        pub = n->advertise<geometry_msgs::PoseWithCovarianceStamped>("/corrected_odom_ar", 10);
        pub_odom = n->advertise<nav_msgs::Odometry>("/odometry/ar", 10);
        sub = n->subscribe("ar_pose_marker",1000, &ar::marker_pose, this);
        sub_odom = n->subscribe("odometry/filtered2",1000, &ar::odom_callback, this);
     
    }

    void marker_pose(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr& msg);
    void odom_callback(nav_msgs::Odometry msg);

};

void ar::odom_callback(nav_msgs::Odometry msg){
    odom.pose.pose.orientation = msg.pose.pose.orientation;
    odom = msg;
}


void ar::marker_pose(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr& msg)
{
    // arrays containing ar tag location
    // std::array<float, 16>;
    float location_x[16]={0.00, 9.80, 9.80, 34.00, 23.63, 10.27, 10.10, 5.44, 31.00, 18.37, 1.36, 17.00, 19.63, 18.29, 18.29, 3.02};
    float location_y[16]={0.00, 0.00, 3.5, 1.5, -4.62, 9.76, -21.38, -15.17, -9.13, 11.00, 9.6, -22.46, -0.02, -13.90, -13.90, -17.34};
    float location_z[16]={0.27146, 0.27167, 0.27166, 0.27182, 0.27159, 0.27163, 0.27225, 0.27188, 0.27203, 0.27204, 0.27151, 0.27164, 0.27196, 0.27145};
    float x,y,z;
    float x_cam_world, y_cam_world, z_cam_world;
    float x_cam_bl, y_cam_bl, z_cam_bl;
    float x_bl_world, y_bl_world, z_bl_world;
    float dist;

    if(!msg->markers.empty()){

   
    ar_track_alvar_msgs::AlvarMarker tag;
    tag.id=msg->markers[0].id;
    std::cout<<"Tag id detected "<<tag.id<<std::endl;

    // ar_wrt_camera
    tag.pose.pose.position=msg->markers[0].pose.pose.position;
    tag.pose.pose.orientation=msg->markers[0].pose.pose.orientation;


    // ar_wrt_world
    x = location_x[tag.id];
    y = location_y[tag.id];
    z = location_z[tag.id] + 0.15;
    
    // cam_wrt_world
    x_cam_world = x-tag.pose.pose.position.x;
    y_cam_world = y-tag.pose.pose.position.y;
    z_cam_world = z-tag.pose.pose.position.z;
    
    // cam_wrt_baselink
    x_cam_bl = 0.0971;
    y_cam_bl = 0;
    z_cam_bl = 0.15513;

    // baselink_wrt_world
    x_bl_world = x_cam_world - x_cam_bl;
    y_bl_world = y_cam_world - y_cam_bl;
    z_bl_world = z_cam_world - z_cam_bl;

    /* Publishing all data as new /Odometry/filtered */

    geometry_msgs::PoseWithCovarianceStamped final;
    final.header = pose_header.header;
    final.header.frame_id = "odom";
    // final.child_frame_id = "base_footprint"; 
    // PoseWithCovariance
    final.pose.pose.position.x = x_bl_world;
    final.pose.pose.position.y = y_bl_world;
    final.pose.pose.position.z = z_bl_world;
    final.pose.pose.orientation = odom.pose.pose.orientation;
    final.pose.covariance = {0.0001,0.0,0.0,0.0,0.0,0.0,
                                0.0,0.0001,0.0,0.0,0.0,0.0,
                                0.0,0.0,0.0001,0.0,0.0,0.0,
                                0.0,0.0,0.0,0.0,0.0,0.0,
                                0.0,0.0,0.0,0.0,0.0,0.0,
                                0.0,0.0,0.0,0.0,0.0,0.0};

    pub.publish(final);
    
    // correcting odom 

    dist = sqrt(pow(x-x_bl_world,2)-pow(y-y_bl_world,2));
    std::cout<<dist;
    if(dist < 1 && (tag.id == 1 || tag.id == 2)){
     
            
            // std::cout<<"\nlol"<<std::endl;
            // int system (const char *command);
            // std::string cmd("rosservice call /set_pose \"pose: \nheader: \n seq: 0 \n stamp: \n  secs: 0 \n  nsecs: 0 \n frame_id: 'odom' \npose: \n pose: \n  position: {x: ");
            // cmd += std::to_string(x_bl_world);
            // cmd += ", y: ";
            // cmd += std::to_string(y_bl_world);
            // cmd += ", z: 0.0} \n  orientation: {x: 0.0, y: 0.0, z: 0.0, w: 0.0} \n covariance: [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]\"";

        

            std::string cmd("rosservice call /set_pose \"{pose: {header: {stamp: {secs: 0, nsecs: 0}, frame_id: odom, seq: 0}, pose: {pose: {position: {y: ");
            cmd += std::to_string(y_bl_world);
            cmd += ", x: ";
            cmd += std::to_string(x_bl_world);
            cmd += ", z: 0.0}, orientation: {y: ";
            cmd += std::to_string(final.pose.pose.orientation.y);
            cmd += ", x: ";
            cmd += std::to_string(final.pose.pose.orientation.x);
            cmd += ", z: ";
            cmd += std::to_string(final.pose.pose.orientation.z);
            cmd += ", w: ";
            cmd += std::to_string(final.pose.pose.orientation.w);
            cmd += "}}, covariance: [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]}}}\"";


            std::cout<<"\n -------- \n";
            std::cout<<std::endl<<cmd<<std::endl;
            std::cout<<"\n -------- \n";

            system(cmd.c_str());
            std::cout<<"\nlol7777777777777777777"<<std::endl;
            
  
            // pub_odom.publish(odom);
    }
         
      
    else if(dist > 1 && (tag.id == 1 || tag.id == 2)){

        pub_odom.publish(odom);
        // std::cout<<"\nlol3"<<std::endl;
    }

    }

    else{
        std::cout<<"No AR TAG in view"<<std::endl;
        pub_odom.publish(odom);
        // std::cout<<"\nlol4"<<std::endl;
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "ar_localisation");
    ros::NodeHandle n;
    ar ob(&n);
    ros::spin();
    return 0;
}
