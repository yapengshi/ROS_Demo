#include "usercommand/talker.h"
#include <usercommand/Num.h>
#include <ncurses.h>


namespace talker {

enum YCursorRows {HEADING=1, STEPNUM=2, DURATION, CLOSE, END};
static constexpr int Y_STATUS      = END+1;
static constexpr int X_KEY         = 1;
static constexpr int X_DESCRIPTION = 10;
static constexpr int X_VALUE       = 35;


Talk::Talk()
{
  ::ros::NodeHandle n;
  user_command_pub_ =n.advertise<usercommand::Num>("/talker/usercommand",1000);
  n_steps_ = 3;
  total_duration_ = 4.0;
  PrintScreen();
}

void
Talk::CallbackKey (int c)
{

  switch (c) {
    case KEY_RIGHT:
      n_steps_ -= 1;
      break;
    case KEY_LEFT:
      n_steps_ += 1;
      break;

    // duration
    case KEY_DOWN:
      total_duration_ += 0.2;
    break;
    case KEY_UP:
      total_duration_ -= 0.2;
    break;
    case 'q':
      printw("Closing user interface\n");
      ros::shutdown(); break;
    default:
      break;
  }
  PublishCommand();
}

void Talk::PublishCommand()
{
  usercommand::Num msg;
  for(int i=0;i<=n_steps_;i++)
  {
    msg.n_steps = i;
    double t_m = 1.0;
    int n_duration = static_cast<int> (total_duration_/t_m);
    for(int j=0;j<=n_duration;j++)
    {
      msg.total_duration = j*t_m;
      user_command_pub_.publish(msg);
    }
  }
}
void
Talk::PrintScreen() const
{
  wmove(stdscr, HEADING, X_KEY);
  printw("Key");
  wmove(stdscr, HEADING, X_DESCRIPTION);
  printw("Description");
  wmove(stdscr, HEADING, X_VALUE);
  printw("Value");

  wmove(stdscr, STEPNUM, X_KEY);
  printw("KEY_LR");
  wmove(stdscr, STEPNUM, X_DESCRIPTION);
  printw("Number of Steps");
  wmove(stdscr, STEPNUM, X_VALUE);
  printw("%d", n_steps_);

  wmove(stdscr, DURATION, X_KEY);
  printw("KEY_UD");
  wmove(stdscr, DURATION, X_DESCRIPTION);
  printw("Duration");
  wmove(stdscr, DURATION, X_VALUE);
  printw("%.2f [s]", total_duration_);

  wmove(stdscr, CLOSE, X_KEY);
  printw("q");
  wmove(stdscr, CLOSE, X_DESCRIPTION);
  printw("Close user interface");
  wmove(stdscr, CLOSE, X_VALUE);
  printw("-");

  wmove(stdscr, Y_STATUS, X_KEY);
  printw("Status:");
}

} /* namespace talk */


int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");

  initscr();
  cbreak();              // disables buffering of types characters
  noecho();              // suppresses automatic output of typed characters
  keypad(stdscr, TRUE);  // to capture special keypad characters
  talker::Talk talk_user_command;

  while (ros::ok())
  {
    int c = getch();
    talk_user_command.CallbackKey(c);
    refresh();
  }
  endwin();

  return 1;
}
