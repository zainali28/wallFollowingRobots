#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#include <webots/Emitter.hpp>
#include <webots/Receiver.hpp>
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
#include <webots/Keyboard.hpp>

#include "Constants.hpp"

class RobotInterface : public webots::Robot
{
public:
    RobotInterface();
    virtual ~RobotInterface();

    // TODO: Implement this function
    void run();

protected:
    // TODO: Implement these functions in the child class
    virtual void moveRobot(Movement mov, Turn dir) = 0;
    virtual bool checkWall(Direction dir) = 0;
    virtual double distanceToWall(Direction dir) = 0;

    // TODO: Add any additional member functions or variables as required
    void addToLog(LogInfo log);
    void followWall();
    void keyboardController();
    webots::Keyboard *userControl;
    bool loadConfig(const std::string &filePath);
    bool keyboardControl;

    // Do not edit the functions below
    void sendMessage(const std::string &data);
    std::string receiveMessage();

private:
    webots::Receiver *mReceiver;
    webots::Emitter *mEmitter;
};
