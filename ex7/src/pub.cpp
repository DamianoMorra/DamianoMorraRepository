#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "boost/thread.hpp"
#include "sensor_msgs/JointState.h"

using namespace std;

class EX7PUB {

	public:
		EX7PUB();
		void CB_sub1(std_msgs::Float64ConstPtr);
		void CB_sub2(std_msgs::Float64ConstPtr);
		void CB_sub3(std_msgs::Float64ConstPtr);
		void CB_sub4(std_msgs::Float64ConstPtr);
		void CB_sub5(std_msgs::Float64ConstPtr);
		void CB_sub6(std_msgs::Float64ConstPtr);
		void CB_sub7(std_msgs::Float64ConstPtr);

	private:
		ros::NodeHandle _nh;

		sensor_msgs::JointState _js_msg;

		ros::Subscriber _j_pos_sub1;
		ros::Subscriber _j_pos_sub2;
		ros::Subscriber _j_pos_sub3;
		ros::Subscriber _j_pos_sub4;
		ros::Subscriber _j_pos_sub5;
		ros::Subscriber _j_pos_sub6;
		ros::Subscriber _j_pos_sub7;

		ros::Publisher _j_pub;

};



EX7PUB::EX7PUB() {

	_j_pos_sub1 = _nh.subscribe("/Coppelia/j1_pos", 0, &EX7PUB::CB_sub1, this);
	_j_pos_sub2 = _nh.subscribe("/Coppelia/j2_pos", 0, &EX7PUB::CB_sub2, this);
	_j_pos_sub3 = _nh.subscribe("/Coppelia/j3_pos", 0, &EX7PUB::CB_sub3, this);
	_j_pos_sub4 = _nh.subscribe("/Coppelia/j4_pos", 0, &EX7PUB::CB_sub4, this);
	_j_pos_sub5 = _nh.subscribe("/Coppelia/j5_pos", 0, &EX7PUB::CB_sub5, this);
	_j_pos_sub6 = _nh.subscribe("/Coppelia/j6_pos", 0, &EX7PUB::CB_sub6, this);
	_j_pos_sub7 = _nh.subscribe("/Coppelia/j7_pos", 0, &EX7PUB::CB_sub7, this);

	_j_pub = _nh.advertise<sensor_msgs::JointState>("joint_states",0);


	_js_msg.name.resize(7);
	_js_msg.position.resize(7);

	_js_msg.name[0]="iiwa_joint_1";
	_js_msg.name[1]="iiwa_joint_2";
	_js_msg.name[2]="iiwa_joint_3";
	_js_msg.name[3]="iiwa_joint_4";
	_js_msg.name[4]="iiwa_joint_5";
	_js_msg.name[5]="iiwa_joint_6";
	_js_msg.name[6]="iiwa_joint_7";

}

void EX7PUB::CB_sub1( std_msgs::Float64ConstPtr j_pos) {
	_js_msg.position[0]=j_pos->data;
	_j_pub.publish(_js_msg);
}
void EX7PUB::CB_sub2( std_msgs::Float64ConstPtr j_pos) {
	_js_msg.position[1]=j_pos->data;
	_j_pub.publish(_js_msg);
}
void EX7PUB::CB_sub3( std_msgs::Float64ConstPtr j_pos) {
	_js_msg.position[2]=j_pos->data;
	_j_pub.publish(_js_msg);
}
void EX7PUB::CB_sub4( std_msgs::Float64ConstPtr j_pos) {
	_js_msg.position[3]=j_pos->data;
	_j_pub.publish(_js_msg);
}
void EX7PUB::CB_sub5( std_msgs::Float64ConstPtr j_pos) {
	_js_msg.position[4]=j_pos->data;
	_j_pub.publish(_js_msg);
}
void EX7PUB::CB_sub6( std_msgs::Float64ConstPtr j_pos) {
	_js_msg.position[5]=j_pos->data;
	_j_pub.publish(_js_msg);
}
void EX7PUB::CB_sub7( std_msgs::Float64ConstPtr j_pos) {
	_js_msg.position[6]=j_pos->data;
	_j_pub.publish(_js_msg);
}


int main( int argc, char** argv ) {
	GLOB_J=0;
	ros::init( argc, argv, "ex7");
	EX7PUB pm;

	ros::spin();
	return 0;
}

