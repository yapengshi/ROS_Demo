
#ifndef TALK_H_
#define TALK_H_

#include <ros/ros.h>

namespace talker {

class Talk {
public:

  Talk ();
  virtual ~Talk () = default;

  void CallbackKey(int c);

private:
  ::ros::Publisher  user_command_pub_; ///< the output message to TOWR.
  int n_steps_;
  double total_duration_;


  void PublishCommand();
  void PrintScreen() const;

};

} /* namespace talk */

#endif /* TALK_H_ */
