#pragma once
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

class Window;

class EngineTime
{
public:
    static void initialize();
    static double getDeltaTime();

private:
    EngineTime();
    ~EngineTime();
    EngineTime(EngineTime const&) {}
    EngineTime& operator=(EngineTime const&) {}

    static EngineTime* instance;

    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point end;

    double deltaTime = 0.0;

    static void logFrameStart();
    static void logFrameEnd();

    friend class Window;

};

