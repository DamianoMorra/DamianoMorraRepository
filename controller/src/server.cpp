#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <actionlib/server/simple_action_server.h>
#include "controller/act1Action.h"
#include <iostream>
#include <sstream>

class action_class {

	private:
  	ros::NodeHandle nh_;
  	actionlib::SimpleActionServer<controller::act1Action> as;
	controller::act1Feedback feedback;
	controller::act1Result result;

  	std::string action_name;
  	int goal;
  	int q;

	public:
		action_class(std::string name) :
  	  		as(nh_, "ACTION_SPACE", boost::bind(&action_class::executeCB, this, _1), false),
  	  		action_name(name) {
				as.registerPreemptCallback(boost::bind(&action_class::preemptCB, this));
				as.start();
  			}
	
		void preemptCB(){
			ROS_WARN("%s got preempted!", action_name.c_str());
			result.status = 1;
			as.setPreempted(result,"I got Preempted"); 
  	}
  
		void executeCB(const controller::act1GoalConstPtr &goal) {

			if(!as.isActive() || as.isPreemptRequested()) return;
			ROS_INFO("%s is processing the goal", action_name.c_str());

			ros::Rate rate(10);
			float qi = goal->qi;
			float qf = goal->qf;
			float dqc = goal->dqc;
			float tf = goal->tf;
			float tc = (qi-qf+dqc*tf)/(dqc);
			float ddqc = (dqc*dqc)/(qi-qf+dqc*tf);
			float t=0;

			for(float time=0; time<=tf*10 ;time++){
				
				t=time/10;

				if (!ros::ok()) {
					result.status = -1;
					as.setAborted(result,"I failed !");
					ROS_INFO("%s Shutting down",action_name.c_str());
					break;
				}
		
				if(!as.isActive() || as.isPreemptRequested()){
					return;
				}	

				//Elaborate current state
				if(t<=tc){
					q=qi+0.5*ddqc*(t*t);
				}else if(t<=(tf - tc)){
					q=qi+ddqc*tc*(t-(tc/2));
				}else{
					q=qf-0.5*ddqc*(tf-t)*(tf-t);
				}

				//Publish current state
				ROS_INFO("Control: %d",q);
				feedback.q = q;
				as.publishFeedback(feedback);

				rate.sleep();

			}

			
				ROS_INFO("Task accomplished");
				result.status = 3;
				as.setSucceeded(result);
				q=0;
			
  }
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "server");
  action_class NH(ros::this_node::getName());
  ROS_INFO("Starting Server");

  ros::spin();
  return 0;
}
