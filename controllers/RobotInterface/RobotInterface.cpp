#include "RobotInterface.hpp"

RobotInterface::RobotInterface()
    : mReceiver{getReceiver("receiver")}, mEmitter{getEmitter("emitter")}
{
    this->keyboardControl = loadConfig("D:\\Freelance\\robotics\\webots-kushal-0128-main\\controllers\\KheperaController\\config.txt");

    this->userControl = new webots::Keyboard();
    this->userControl->enable(TIME_STEP);
    this->mReceiver->enable(TIME_STEP);
}

RobotInterface::~RobotInterface()
{
    mReceiver->disable();
}

// TODO: Add any additional function definitions here
bool RobotInterface::loadConfig(const std::string &filePath)
{
    std::ifstream configFile(filePath);
    std::string line;

    if (!configFile.is_open())
    {
        std::cerr << "Error: Could not open config file: " << filePath << std::endl;
        return false;
    }

    while (getline(configFile, line))
    {
        // Parse the line for 'keyboardControl' command
        size_t pos = line.find("keyboardControl=");
        if (pos != std::string::npos)
        {
            std::string value = line.substr(pos + 16); // Extract the value part
            if (value == "true")
            {
                return true; // Enable keyboard control
            }
            else if (value == "false")
            {
                return false; // Disable keyboard control
            }
        }
    }

    std::cerr << "Error: 'keyboardControl' not found in config file!" << std::endl;
    return false; // Default to autonomous if the command is not found
}
void RobotInterface::followWall()
{
    bool isFront = this->checkWall(Direction::FRONT);
    bool isLeft = this->checkWall(Direction::LEFT);
    bool isRight = this->checkWall(Direction::RIGHT);
    Turn wall = Turn::LEFT;
    bool init = true;

    if (isLeft && init)
    {
        wall = Turn::LEFT;
        init = false;
    }
    else if (isRight && init)
    {
        wall = Turn::RIGHT;
        init = false;
    }

    switch (wall)
    {
    case Turn::LEFT:
    {
        if (isLeft && !isFront && !isRight)
        {
            this->moveRobot(Movement::FORWARDS, Turn::STRAIGHT);
        }
        if (!isFront && !isRight && !isLeft)
        {
            this->moveRobot(Movement::FORWARDS, Turn::LEFT);
        }
        else if (!isFront && !isLeft && isRight)
        {
            this->moveRobot(Movement::FORWARDS, Turn::LEFT);
        }
        if (isFront)
        {
            this->moveRobot(Movement::FORWARDS, Turn::RIGHT);
        }
        break;
    }
    case Turn::RIGHT:
    {
        break;
    }

    default:
        break;
    }
}

void RobotInterface::keyboardController()
{
    const int KEY_W = 'W';
    const int KEY_A = 'A';
    const int KEY_S = 'S';
    const int KEY_D = 'D';

    this->moveRobot(Movement::STOP, Turn::STRAIGHT);

    switch (this->userControl->getKey())
    {
    case KEY_W:
    {
        this->moveRobot(Movement::FORWARDS, Turn::STRAIGHT);
        break;
    }
    case KEY_S:
    {
        this->moveRobot(Movement::BACKWARDS, Turn::STRAIGHT);
        break;
    }
    case KEY_A:
    {
        this->moveRobot(Movement::FORWARDS, Turn::LEFT);
        break;
    }
    case KEY_D:
    {
        this->moveRobot(Movement::FORWARDS, Turn::RIGHT);
        break;
    }

    default:
    {
        this->moveRobot(Movement::STOP, Turn::STRAIGHT);
        break;
    }
    }
}

void RobotInterface::run()
{
    while (this->step(TIME_STEP) != -1)
    {
        if (this->keyboardControl)
            this->keyboardController();
        else
            this->followWall();
    }
}

// Do not change this function, use it as-is
void RobotInterface::sendMessage(const std::string &data)
{
    mEmitter->send(data.c_str(), static_cast<int>(strlen(data.c_str())) + 1);
}

// Do not change this function, use it as-is
std::string RobotInterface::receiveMessage()
{
    if (mReceiver->getQueueLength() > 0)
    {
        std::string message{static_cast<const char *>(mReceiver->getData())};
        mReceiver->nextPacket();

        return message;
    }
    return "";
}