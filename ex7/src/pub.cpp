#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "boost/thread.hpp"
#include "sensor_msgs/JointState.h"

using namespace std;

int GLOB_J;


class PAN_MOTION {

	public:
		PAN_MOTION();
		void ctrl_loop();
		void joint_data_sub(std_msgs::Float64ConstPtr);
		void run();

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



PAN_MOTION::PAN_MOTION() {

	_j_pos_sub1 = _nh.subscribe("/Coppelia/j1_pos", 0, &PAN_MOTION::joint_data_sub, this);
	_j_pos_sub2 = _nh.subscribe("/Coppelia/j2_pos", 0, &PAN_MOTION::joint_data_sub, this);
	_j_pos_sub3 = _nh.subscribe("/Coppelia/j3_pos", 0, &PAN_MOTION::joint_data_sub, this);
	_j_pos_sub4 = _nh.subscribe("/Coppelia/j4_pos", 0, &PAN_MOTION::joint_data_sub, this);
	_j_pos_sub5 = _nh.subscribe("/Coppelia/j5_pos", 0, &PAN_MOTION::joint_data_sub, this);
	_j_pos_sub6 = _nh.subscribe("/Coppelia/j6_pos", 0, &PAN_MOTION::joint_data_sub, this);
	_j_pos_sub7 = _nh.subscribe("/Coppelia/j7_pos", 0, &PAN_MOTION::joint_data_sub, this);

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

void PAN_MOTION::joint_data_sub( std_msgs::Float64ConstPtr j_pos) {

	//ROS_INFO("J %d : %f", GLOB_J, j_pos->data);
	GLOB_J++;
	if(GLOB_J==8){GLOB_J=1;}

	_js_msg.position[GLOB_J-1]=j_pos->data;
	_j_pub.publish(_js_msg);

	//sleep(1);
}


void PAN_MOTION::ctrl_loop() {
}

void PAN_MOTION::run() {

	boost::thread ctrl_loop_t( &PAN_MOTION::ctrl_loop, this);
	ros::spin();
}

int main( int argc, char** argv ) {
	GLOB_J=0;
	ros::init( argc, argv, "ex7");
	PAN_MOTION pm;
	pm.run();

	return 0;
}

