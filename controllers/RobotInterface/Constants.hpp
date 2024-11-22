#pragma once

// TODO: This definition may be changed if required
enum class Movement
{
    FORWARDS,
    BACKWARDS,
    STOP,
};

// TODO: This definition may be changed if required
enum class Turn
{
    STRAIGHT,
    LEFT,
    RIGHT,

};

enum class Direction
{
    FRONT,
    BACK,
    LEFT,
    RIGHT
};

struct LogInfo
{
    bool wallLeft;
    bool wallRight;
    bool wallFront;
    double bearing;
};

constexpr int TIME_STEP{64};

// TODO: Add any additional global constants as required
constexpr float MAX_SPEED{10.0};