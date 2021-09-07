#include "ros/ros.h"
#include "std_msgs/Header.h"
#include "std_msgs/String.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "geometry_msgs/PoseWithCovariance.h"
#include "geometry_msgs/PoseStamped.h"

class pose{
    private:
    ros::Publisher pub;
    ros::Subscriber sub;

    public:
    pose(ros::NodeHandle *nh){
    sub = nh->subscribe("/wheel_pose", 1, &pose::pose_callback, this);
    pub = nh->advertise<geometry_msgs::PoseWithCovarianceStamped> ("/wheel_odom_pose", 10);
    }

    void pose_callback(const geometry_msgs::PoseStamped::ConstPtr& msg);

};


void pose::pose_callback(const geometry_msgs::PoseStamped::ConstPtr& msg){
    ros::Rate loop_rate(10);
    geometry_msgs::PoseWithCovarianceStamped data;

    data.header = msg->header;
    data.pose.covariance = {0.0001,0.0,0.0,0.0,0.0,0.0,
                                0.0,0.0,0.0,0.0,0.0,0.0,
                                0.0,0.0,0.0,0.0,0.0,0.0,
                                0.0,0.0,0.0,0.0,0.0,0.0,
                                0.0,0.0,0.0,0.0,0.0,0.0,
                                0.0,0.0,0.0,0.0,0.0,0.0001};
    data.pose.pose = msg->pose;
    pub.publish(data);
    loop_rate.sleep();

}

int main(int argc, char** argv){
   
    ros::init(argc, argv, "wheel_odom_pose_repub");
    ros::NodeHandle nh;
    
    pose obj = pose(&nh);

    ros::spin();
    return 0;

}
