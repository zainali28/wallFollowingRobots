#pragma once

#include "../RobotInterface/RobotInterface.hpp"

class Rosbot : public RobotInterface
{
public:
  Rosbot();
  ~Rosbot();

private:
  void moveRobot(Movement mov, Turn dir) override;
  bool checkWall(Direction dir) override;
  double distanceToWall(Direction dir) override;

  // TODO: Add additional functions and members as required
  webots::Motor *frontLeftMotor;
  webots::Motor *frontRightMotor;
  webots::Motor *rearLeftMotor;
  webots::Motor *rearRightMotor;
};
