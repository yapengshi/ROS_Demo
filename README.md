# ROS_Demo
This repository is created to save some demos with the code of ROS &amp; C++.
My Computer: Ubuntu 16.04.5 LTS and ROS-Kinetic.
* Install dependencies [CMake], [catkin], [ROS], [ncurses], [xterm]:
  ```bash
  sudo apt-get install cmake libncurses5-dev xterm
  sudo apt-get install ros-<ros-distro>-desktop-full
  ```
  * Install ROS_Demo

  ```bash
  git clone https://github.com/yapengshi/ROS_Demo.git
  cd ROS_Demo/rosio/
  catkin build  #(Recommend)
  source devel/setup.bash 
  roslaunch usercommand talker.launch
  ```
Then we can change the input variables wia key_UP/DOWN/LEFT/RIGHT
Please note it is the for loop, you can change in your idea.

  
