#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "boost/thread.hpp"
#include "sensor_msgs/JointState.h"

using namespace std;

int GLOB_J;


class PAN_MOTION {

	public:
		PAN_MOTION();
		void ctrl_loop();
		void joint_data_sub(std_msgs::Float32ConstPtr);
		void run();

	private:
		ros::NodeHandle _nh;

		sensor_msgs::JointState joint_states;

		ros::Subscriber _j_pos_sub1;
		ros::Subscriber _j_pos_sub2;
		ros::Subscriber _j_pos_sub3;
		ros::Subscriber _j_pos_sub4;
		ros::Subscriber _j_pos_sub5;
		ros::Subscriber _j_pos_sub6;
		ros::Subscriber _j_pos_sub7;

		ros::Publisher _j_pos_pub1;

};



PAN_MOTION::PAN_MOTION() {

	_j_pos_sub1 = _nh.subscribe("/iiwa/j1/pos", 0, &PAN_MOTION::joint_data_sub, this);
	_j_pos_sub2 = _nh.subscribe("/iiwa/j2/pos", 0, &PAN_MOTION::joint_data_sub, this);
	_j_pos_sub3 = _nh.subscribe("/iiwa/j3/pos", 0, &PAN_MOTION::joint_data_sub, this);
	_j_pos_sub4 = _nh.subscribe("/iiwa/j4/pos", 0, &PAN_MOTION::joint_data_sub, this);
	_j_pos_sub5 = _nh.subscribe("/iiwa/j5/pos", 0, &PAN_MOTION::joint_data_sub, this);
	_j_pos_sub6 = _nh.subscribe("/iiwa/j6/pos", 0, &PAN_MOTION::joint_data_sub, this);
	_j_pos_sub7 = _nh.subscribe("/iiwa/j7/pos", 0, &PAN_MOTION::joint_data_sub, this);

	_j_pos_pub1 = _nh.advertise<sensor_msgs::JointState>("joint_states",1);

}

void PAN_MOTION::joint_data_sub( std_msgs::Float32ConstPtr j_pos) {

	ROS_INFO("J %d : %f", GLOB_J, j_pos->data);
	GLOB_J++;
	if(GLOB_J==8){GLOB_J=1;}

joint_states.name.resize(7);
joint_states.position.resize(7);

	joint_states.name[GLOB_J-1]=GLOB_J;
	joint_states.position[GLOB_J-1]=j_pos->data;

	_j_pos_pub1.publish(joint_states);

	//sleep(1);
}


void PAN_MOTION::ctrl_loop() {
}

void PAN_MOTION::run() {

	boost::thread ctrl_loop_t( &PAN_MOTION::ctrl_loop, this);
	ros::spin();
}

int main( int argc, char** argv ) {
	GLOB_J=1;
	ros::init( argc, argv, "pan_control");
	PAN_MOTION pm;
	pm.run();

	return 0;
}

