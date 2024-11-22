#include "Khepera.hpp"

Khepera::Khepera()
{

    this->IRSensors[0] = this->getDistanceSensor("front infrared sensor");
    this->IRSensors[1] = this->getDistanceSensor("front left infrared sensor");
    this->IRSensors[2] = this->getDistanceSensor("front right infrared sensor");
    this->IRSensors[3] = this->getDistanceSensor("left infrared sensor");
    this->IRSensors[4] = this->getDistanceSensor("right infrared sensor");
    this->IRSensors[5] = this->getDistanceSensor("rear infrared sensor");
    this->IRSensors[6] = this->getDistanceSensor("rear left infrared sensor");
    this->IRSensors[7] = this->getDistanceSensor("rear right infrared sensor");

    for (int i = 0; i < 8; i++)
    {
        this->IRSensors[i]->enable(TIME_STEP);
        IRSensorVals[i] = (double)this->IRSensors[i]->getValue();
        IRSensorVals[i] = Khepera::val2dist(IRSensorVals[i]);
    }

    leftMotor = this->getMotor("left wheel motor");
    rightMotor = this->getMotor("right wheel motor");
    leftMotor->setPosition(INFINITY);
    rightMotor->setPosition(INFINITY);
    leftMotor->setVelocity(0.0);
    rightMotor->setVelocity(0.0);
}

Khepera::~Khepera() {}

bool Khepera::checkWall(Direction dir)
{
    for (int i = 0; i < 8; i++)
    {
        IRSensorVals[i] = (double)this->IRSensors[i]->getValue();
        IRSensorVals[i] = Khepera::val2dist(IRSensorVals[i]);
        std::cout << "[" << i << "]: " << IRSensorVals[i] << std::endl;
    }

    switch (dir)
    {
    case Direction::FRONT:
    {
        if (IRSensorVals[0] <= 0.16 || IRSensorVals[1] <= 0.16 || IRSensorVals[2] <= 0.16)
            return true;
        break;
    }
    case Direction::LEFT:
    {
        if (IRSensorVals[3] <= 0.16)
            return true;
        break;
    }
    case Direction::RIGHT:
    {
        if (IRSensorVals[4] <= 0.16)
            return true;
        break;
    }

    default:
        return false;
        break;
    }

    return false;
}

void Khepera::moveRobot(Movement mov, Turn dir)
{
    float leftMotorSpeed = 0.0;
    float rightMotorSpeed = 0.0;
    switch (mov)
    {
    case Movement::FORWARDS:
    {
        leftMotorSpeed = 0.5;
        rightMotorSpeed = 0.5;
        break;
    }
    case Movement::BACKWARDS:
    {
        leftMotorSpeed = -0.5;
        rightMotorSpeed = -0.5;
        break;
    }
    case Movement::STOP:

    default:
    {
        leftMotorSpeed = 0.0;
        rightMotorSpeed = 0.0;
        break;
    }
    }

    switch (dir)
    {
    case Turn::STRAIGHT:
    {
        if (mov == Movement::FORWARDS)
        {
            leftMotorSpeed = 0.5;
            rightMotorSpeed = 0.5;
        }
        else if (mov == Movement::BACKWARDS)
        {
            leftMotorSpeed = -0.5;
            rightMotorSpeed = -0.5;
        }
        break;
    }
    case Turn::LEFT:
    {
        if (mov == Movement::FORWARDS)
        {
            leftMotorSpeed = 0.2;
        }
        else if (mov == Movement::BACKWARDS)
        {
            leftMotorSpeed = -0.2;
        }
        leftMotorSpeed = -leftMotorSpeed;
        break;
    }

    case Turn::RIGHT:
    {
        if (mov == Movement::FORWARDS)
        {
            rightMotorSpeed = 0.2;
        }
        else if (mov == Movement::BACKWARDS)
        {
            rightMotorSpeed = -0.2;
        }
        rightMotorSpeed = 0.2;
        rightMotorSpeed = -rightMotorSpeed;
        break;
    }

    default:
        break;
    }

    this->leftMotor->setVelocity(leftMotorSpeed * MAX_SPEED);
    this->rightMotor->setVelocity(rightMotorSpeed * MAX_SPEED);
}

double Khepera::distanceToWall(Direction dir)
{
    switch (dir)
    {
    case Direction::FRONT:
        return this->val2dist((this->IRSensors[0]->getValue()));
        break;
    case Direction::LEFT:
        return this->val2dist((this->IRSensors[3]->getValue()));
        break;
    case Direction::RIGHT:
        return this->val2dist((this->IRSensors[4]->getValue()));
        break;

    default:
        break;
    }

    return -1;
}

double Khepera::val2dist(double val)
{
    return 0.2 - ((val / 1023) * 0.2);
}