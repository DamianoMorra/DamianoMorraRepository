#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "std_msgs/String.h"
#include "randex/custom1.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv){
	ros::init(argc, argv, "Node1"); 
	ros::NodeHandle nh;  
	ros::Publisher topic_pub = nh.advertise <randex::custom1> ("pacchetto",10); 
	ros::Rate rate(10); //10Hz

	while(ros::ok()){

		randex::custom1 msg;

		msg.rand1 = rand();
		msg.rand2 = rand();

		topic_pub.publish(msg);
		ROS_INFO("Inviato 1: %f", msg.rand1);
		ROS_INFO("Inviato 2: %f", msg.rand2);
		cout<<endl;

		rate.sleep();
	}	
}
