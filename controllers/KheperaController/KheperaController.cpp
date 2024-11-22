#include "Khepera.hpp"
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/Keyboard.hpp>

#define TIME_STEP 64

int main(int argc, char **argv)
{
  Khepera *robot = new Khepera();

  robot->run();

  return 0;
}