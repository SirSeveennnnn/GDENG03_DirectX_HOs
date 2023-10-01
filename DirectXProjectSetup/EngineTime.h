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

    static void LogFrameStart();
    static void LogFrameEnd();

    

private:
    EngineTime();
    ~EngineTime();

    EngineTime(EngineTime const&){};
    EngineTime& operator=(EngineTime const&) {};


    static EngineTime* sharedInstance;

    chrono::system_clock::time_point start;
    chrono::system_clock::time_point end;

    double deltaTime = 0.0f;

    

    friend class Window;


};

