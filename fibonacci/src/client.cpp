#include "ros/ros.h"
#include <sstream>
#include <iostream>
#include "fibonacci/service.h"

using namespace std;


int main (int argc, char** argv){

	ros::init(argc, argv, "service_client");
	ros::NodeHandle nh;

	ros::Rate loop_rate(10);
	ros::ServiceClient client = nh.serviceClient<fibonacci::service>("service");

	while(ros::ok()){
		fibonacci::service srv;

		cout<<"Index:";
		cin>>srv.request.index;
		cout<<"Length:";
		cin>>srv.request.length;

		if(client.call(srv)){
			cout<<"Input: [" <<srv.request.index <<"]["<<srv.request.length <<"]" <<endl;
		}
		else{
			ROS_ERROR("Failed to call service");
		}

		cout<<endl;

	ros::spinOnce();
	loop_rate.sleep();

	}
	return 1;

}