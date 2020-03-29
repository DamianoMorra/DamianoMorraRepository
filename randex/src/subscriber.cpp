#include "ros/ros.h"
#include "std_msgs/String.h"
#include "randex/custom1.h"
#include "randex/custom2.h"
#include <iostream>

using namespace std;

class ROS_SUB{
	public:
		ROS_SUB();
		void topic_cb(randex::custom1::ConstPtr msg);
	private:
		ros::NodeHandle _nh;
		ros::Subscriber _topic_sub;
		ros::Publisher _topic_pub;
	};

ROS_SUB::ROS_SUB(){
	_topic_sub = _nh.subscribe( "pacchetto", 10,&ROS_SUB::topic_cb, this);
	_topic_pub = _nh.advertise <randex::custom2> ("pacchetto2",10); 
}

void ROS_SUB::topic_cb( randex::custom1::ConstPtr msg){
	ROS_INFO("Ricevuto 1: %f", msg->rand1);
	ROS_INFO("Ricevuto 2: %f", msg->rand2);
	cout<<endl;

	randex::custom2 msg2;

	msg2.rand1 = msg->rand1;
	msg2.rand2 = msg->rand2;
	msg2.sum = msg2.rand1 + msg2.rand2;

	_topic_pub.publish(msg2);

};

int main(int argc, char **argv){
	
	ros::init(argc,argv,"Node2");
	ROS_SUB rs;

	ros::spin();  //aspetta solo le callback
}
