#ifndef LISTEN_H_
#define LISTEN_H_

#include <ros/ros.h>
#include <usercommand/Num.h>

namespace listener {

class listen {
public:

  listen ();
  virtual ~listen () = default;

//  void CallbackKey(int c);

private:
  ::ros::Subscriber  user_command_sub_;
  void UserCommandCallback(const usercommand::Num& msg);
//  int n_steps_;
//  double total_duration_;


//  void PublishCommand();
//  void PrintScreen() const;

};

} /* namespace listener */

#endif /* LISTEN_H_ */
