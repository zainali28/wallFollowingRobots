#pragma once

#include "../RobotInterface/RobotInterface.hpp"

class Khepera : public RobotInterface
{
public:
  Khepera();
  ~Khepera();

private:
  void moveRobot(Movement mov, Turn dir) override;
  bool checkWall(Direction dir) override;
  // double distanceToWall(Direction dir) override;

  // TODO: Add additional functions and members as required
  webots::Motor *leftMotor;
  webots::Motor *rightMotor;
  webots::DistanceSensor *IRSensors[8];
  double IRSensorVals[8];
  double val2dist(double val);
};