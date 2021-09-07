#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "move_base_msgs/MoveBaseActionGoal.h"
#include "move_base_msgs/MoveBaseGoal.h"
#include "actionlib_msgs/GoalStatusArray.h"
#include "actionlib_msgs/GoalID.h"
// #include <cmath>

class Cancel
{
	public:
		float goal_x;
		float goal_y;
		float odom_x;
		float odom_y;
		float dist;
		int status;
		bool flag;
		ros::Publisher pub;
		ros::Subscriber sub_stat;
		ros::Subscriber sub_odom;
		ros::Subscriber sub_goal;

	Cancel(ros::NodeHandle *n)
	{
		goal_x =0;
		goal_y=0;
		odom_x =0;
	    	odom_y=0;
		dist =0;
		status=0;
		flag = false;
		pub = n->advertise<actionlib_msgs::GoalID>("/move_base/cancel", 10);
		sub_stat = n->subscribe("/move_base/status",1000, &Cancel::getstat,this);
	    	sub_odom = n->subscribe("/odometry/filtered",1000, &Cancel::getodom,this);
		sub_goal = n->subscribe("/move_base/goal",1000, &Cancel::getgoal,this);
	}
	void getgoal(const move_base_msgs::MoveBaseActionGoal::ConstPtr& msg);
	void getodom(const nav_msgs::Odometry::ConstPtr& odom);
	void getstat(const actionlib_msgs::GoalStatusArray::ConstPtr& stat);
	bool check();
};

void Cancel::getgoal(const move_base_msgs::MoveBaseActionGoal::ConstPtr& msg)
{
	if(msg)
	{
		goal_x = msg->goal.target_pose.pose.position.x;
		goal_y = msg->goal.target_pose.pose.position.y;
		std::cout<<"Received new goal "<< goal_x << goal_y;
	}
}
	
void Cancel::getodom(const nav_msgs::Odometry::ConstPtr& odom)
{
	if(odom)
	{
		odom_x= odom->pose.pose.position.x;
		odom_y= odom->pose.pose.position.y;
		dist = sqrt(pow((odom_x-goal_x),2)+pow((odom_y-goal_y),2));
		std::cout<<"Distance from goal :"<<dist;
		if (!flag)
			flag = &Cancel::check;
		if(flag)
		{
			actionlib_msgs::GoalID goal;
			pub.publish(goal);
			std::cout<<"Reached Goal, Sent cancel command";
			flag=false;
		}
	}
}

bool Cancel::check()
{
	if(status == 0)
		std::cout<<"Waiting for goal to be set";
	else if(status != 2)
		std::cout<<"Moving towards goal";
	if (dist<0.5 and status !=0)
		return true;
	return false;
}

void Cancel::getstat(const actionlib_msgs::GoalStatusArray::ConstPtr& stat)
{
	if(stat)
	{
		status = stat->status_list[0].status;
	}
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "Cancel");
    ros::NodeHandle n;
    Cancel ob=Cancel(&n);
    ros::spin();
    return 0;
}

