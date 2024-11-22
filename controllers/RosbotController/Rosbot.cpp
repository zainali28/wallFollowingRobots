#include "Rosbot.hpp"
#include <iostream>
#include <cmath>

Rosbot::Rosbot()
{
    this->frontLeftMotor = this->getMotor("front left wheel motor");
    this->frontRightMotor = this->getMotor("front right wheel motor");
    this->rearLeftMotor = this->getMotor("rear left wheel motor");
    this->rearRightMotor = this->getMotor("rear right wheel motor");

    this->frontLeftMotor->setPosition(INFINITY);
    this->frontRightMotor->setPosition(INFINITY);
    this->rearLeftMotor->setPosition(INFINITY);
    this->rearRightMotor->setPosition(INFINITY);

    this->frontLeftMotor->setVelocity(0.0);
    this->frontRightMotor->setVelocity(0.0);
    this->rearLeftMotor->setVelocity(0.0);
    this->rearRightMotor->setVelocity(0.0);
}

Rosbot::~Rosbot() {}

void Rosbot::moveRobot(Movement mov, Turn dir)
{
    double frontLeftSpeed = 0.0, frontRightSpeed = 0.0, rearLeftSpeed = 0.0, rearRightSpeed = 0.0;

    switch (mov)
    {
    case Movement::FORWARDS:
        frontLeftSpeed = frontRightSpeed = rearLeftSpeed = rearRightSpeed = 0.5;
        break;
    case Movement::BACKWARDS:
        frontLeftSpeed = frontRightSpeed = rearLeftSpeed = rearRightSpeed = -0.5;
        break;
    case Movement::STOP:
    default:
        break;
    }

    if (dir == Turn::LEFT)
    {
        frontLeftSpeed -= 0.3;
        rearLeftSpeed -= 0.3;
    }
    else if (dir == Turn::RIGHT)
    {
        frontRightSpeed -= 0.3;
        rearRightSpeed -= 0.3;
    }

    frontLeftMotor->setVelocity(frontLeftSpeed * MAX_SPEED);
    frontRightMotor->setVelocity(frontRightSpeed * MAX_SPEED);
    rearLeftMotor->setVelocity(rearLeftSpeed * MAX_SPEED);
    rearRightMotor->setVelocity(rearRightSpeed * MAX_SPEED);
}

bool Rosbot::checkWall(Direction dir)
{
}

double Rosbot::distanceToWall(Direction dir)
{
}
