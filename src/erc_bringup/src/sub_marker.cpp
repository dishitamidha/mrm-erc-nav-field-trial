#include "ros/ros.h"
#include "std_msgs/Header.h"
#include "std_msgs/String.h"
#include "visualization_msgs/Marker.h"
#include "visualization_msgs/MarkerArray.h"
class sub_marker{
    private:
    ros::Publisher pub;
    ros::Subscriber sub;

    public:
    sub_marker(ros::NodeHandle *nh){
    sub = nh->subscribe("visualisation_markers", 1, &sub_marker::marker_callback, this);
    }

    void marker_callback(visualization_msgs::MarkerArray msg);

};

void sub_marker::marker_callback(visualization_msgs::MarkerArray msg){

}

int main(int argc, char** argv){
    
    ros::init(argc, argv, "marker_sub");
    ros::NodeHandle nh;
    
    sub_marker obj = sub_marker(&nh);

    ros::spin();
    return 0;

}
