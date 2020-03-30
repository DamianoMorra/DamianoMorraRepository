#include "ros/ros.h"
#include <iostream>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include "controller/act1Action.h"

int main (int argc, char **argv) {

	ros::init(argc, argv, "client");
  if(argc != 5){
		ROS_INFO("%d",argc);
		ROS_WARN("Usage: <initial position> <desired final position> <maximum rotational velocity> <completion time>");
		return 1;
	}

  // create the action client
  // true causes the client to spin its own thread
  actionlib::SimpleActionClient<controller::act1Action> ac("ACTION_SPACE", true);

  ROS_INFO("Waiting for action server to start.");

  // wait for the action server to start
  ac.waitForServer(); //will wait for infinite time
  ROS_INFO("Action server started, sending info.");

  // Send to server
  controller::act1Goal goal;

  goal.qi = atoi(argv[1]);
  goal.qf = atoi(argv[2]);
  goal.dqc = atoi(argv[3]);
  goal.tf = atoi(argv[4]);

  ROS_INFO("Sending data");

  ac.sendGoal(goal);


  //Condizione di preempt
  controller::act1ResultConstPtr result = ac.getResult();
  actionlib::SimpleClientGoalState state = ac.getState();

  int brack = (abs(goal.qf-goal.qi))/goal.tf;

  if(   (abs(goal.dqc)>brack) && (abs(goal.dqc)<= (2*brack))    ){

    ROS_INFO("ok");
    
  } else{
    ROS_INFO("Desired final position impossible to reach.");    
    ac.cancelGoal();
  }


  //exit
  return 0;
}
