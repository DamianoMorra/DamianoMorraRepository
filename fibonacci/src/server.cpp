#include "ros/ros.h"
#include <sstream>
#include "fibonacci/service.h"
//si crea quando facciamo il catkin_make

using namespace std;

int seq[100];

bool service_callback(fibonacci::service::Request &req, fibonacci::service::Response &res){

	for(int i=stoi(req.index.c_str());i<(stoi(req.index.c_str())+stoi(req.length.c_str()));i++){

		res.out=seq[i];
		ROS_INFO("Output: [%d]",res.out);
	}

	cout<<endl;

	return true;
}

int main (int argc, char** argv){

	seq[0]=0;
	seq[1]=1;
	for(int i=2;i<100;i++){
		seq[i]=seq[i-1]+seq[i-2];
	}


	ros::init(argc, argv, "service_server");
	ros::NodeHandle n;
	ros::ServiceServer service = n.advertiseService("service",service_callback);

	ROS_INFO("ready to get request");


	ros::spin();
	return 0;

}