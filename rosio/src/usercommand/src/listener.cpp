#include "usercommand/listener.h"
#include "usercommand/Num.h"

namespace listener {

listen::listen()
{
  ros::NodeHandle n;
  // use the func() in class, the fourth para add "this"
  user_command_sub_ = n.subscribe("/talker/usercommand",1000, &listen::UserCommandCallback, this);
}

void listen::UserCommandCallback(const usercommand::Num &msg)
{
  ROS_INFO("I heard: [%d]",msg.n_steps);
  ROS_INFO("I heard: [%f]",msg.total_duration);
}


} /// end of the namespace listener


int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  listener::listen listen1;
//  ros::NodeHandle n;
//  ros::Subscriber sub = n.subscribe("/talker/usercommand", 1000, chatterCallback);
  ros::spin();

  return 0;
}
