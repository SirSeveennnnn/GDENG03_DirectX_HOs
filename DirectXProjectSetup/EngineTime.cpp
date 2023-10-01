#include "EngineTime.h"

EngineTime* EngineTime::sharedInstance = nullptr;

void EngineTime::initialize() {
    if (sharedInstance == nullptr) {
        sharedInstance = new EngineTime();
    }
}

double EngineTime::getDeltaTime() {
    return sharedInstance->deltaTime;
}

void EngineTime::LogFrameStart() {
    sharedInstance->start = chrono::system_clock::now();
}

void EngineTime::LogFrameEnd() {
    sharedInstance->end = chrono::system_clock::now();
    chrono::duration<double> elapsedSeconds = sharedInstance->end - sharedInstance->start;
    sharedInstance->deltaTime = elapsedSeconds.count();
}

EngineTime::EngineTime() {
    // Private constructor
}

EngineTime::~EngineTime() {
    // Destructor
    delete sharedInstance;
}