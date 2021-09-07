#include "ros/ros.h"
#include "std_msgs/Header.h"
#include "std_msgs/String.h"
#include "geometry_msgs/TwistWithCovarianceStamped.h"
#include "geometry_msgs/TwistWithCovariance.h"
#include "geometry_msgs/TwistStamped.h"

class twist{
    private:
    ros::Publisher pub;
    ros::Subscriber sub;

    public:
    twist(ros::NodeHandle *nh){
    sub = nh->subscribe("/wheel_odom", 1, &twist::twist_callback, this);
    pub = nh->advertise<geometry_msgs::TwistWithCovarianceStamped> ("/wheel_odom_twist", 10);
    }

    void twist_callback(const geometry_msgs::TwistStamped::ConstPtr& msg);

};


void twist::twist_callback(const geometry_msgs::TwistStamped::ConstPtr& msg){
    ros::Rate loop_rate(10);
    geometry_msgs::TwistWithCovarianceStamped data;

    data.header = msg->header;
    data.header.frame_id = "base_footprint";
    data.twist.covariance = {0.0001,0.0,0.0,0.0,0.0,0.0,
                                0.0,0.0,0.0,0.0,0.0,0.0,
                                0.0,0.0,0.0,0.0,0.0,0.0,
                                0.0,0.0,0.0,0.0,0.0,0.0,
                                0.0,0.0,0.0,0.0,0.0,0.0,
                                0.0,0.0,0.0,0.0,0.0,0.001};
    data.twist.twist = msg->twist;
    pub.publish(data);
    loop_rate.sleep();

}

int main(int argc, char** argv){
   
    ros::init(argc, argv, "wheel_odom_twist_repub");
    ros::NodeHandle nh;
    
    twist obj = twist(&nh);

    ros::spin();
    return 0;

}
